#define _POSIX_C_SOURCE 199309L

#include "../include/convert-video.h"
#include "../include/convert.h"

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

#include <stdlib.h>
#include <time.h>

int convertVideo(const char *filename, const int asciiLength, const char *ascii, const int color, const int outputWidth, const int fps) {
  if (!filename) return 0;

  avformat_network_init();

  AVFormatContext* fmt = NULL;

  avformat_open_input(&fmt, filename, NULL, NULL);
  avformat_find_stream_info(fmt, NULL);

  int vstream = -1;

  for (unsigned int i = 0; i < fmt->nb_streams; i++) {
    if (fmt->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      vstream = i;
      break;
    }
  }

  AVCodecParameters *par = fmt->streams[vstream]->codecpar;
  const AVCodec *dec = avcodec_find_decoder(par->codec_id);

  AVCodecContext *ctx = avcodec_alloc_context3(dec);
  avcodec_parameters_to_context(ctx, par);
  avcodec_open2(ctx, dec, NULL);

  AVFrame *frame = av_frame_alloc();
  AVFrame *rgb = av_frame_alloc();
  
  int width = ctx->width;
  int height = ctx->height;

  uint8_t *buffer = av_malloc(width * height * 3);

  rgb->data[0] = buffer;
  rgb->linesize[0] = width * 3;

  struct SwsContext *sws = sws_getContext(
    width, height, ctx->pix_fmt,
    width, height, AV_PIX_FMT_RGB24,
    SWS_BILINEAR, NULL, NULL, NULL 
  );

  AVPacket pkt;
  
  int msPerFrame = 1000 / fps;
  struct timespec ts;
  ts.tv_sec = msPerFrame / 1000;
  ts.tv_nsec = (msPerFrame % 1000) * 1000000L;

  while (av_read_frame(fmt, &pkt) >= 0) {
    if (pkt.stream_index == vstream) {
      avcodec_send_packet(ctx, &pkt);

      while (avcodec_receive_frame(ctx, frame) == 0) {
        sws_scale(
          sws, (const uint8_t * const *)frame->data,
          frame->linesize, 0, height, rgb->data, rgb->linesize 
        );

        uint8_t *rgbFrame = rgb->data[0];
        
        convert(height, width, outputWidth, ascii, asciiLength, rgbFrame, color, 3); 
        nanosleep(&ts, NULL);
      }
  
      av_packet_unref(&pkt);
    }
  }

  return 1;
}
