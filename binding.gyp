{
"targets": [{
  "target_name": "nodeffms2",
  "sources": [
    "src/ffms2.cc"
  ],
  "conditions": [
    ['OS=="mac"', {
      "cflags" : [
        "-g",
        "-D__STDC_CONSTANT_MACROS",
        "-D_FILE_OFFSET_BITS=64",
        "-D_LARGEFILE_SOURCE",
        "-O3",
        "-Wall"
        "-I${PWD}/deps/ffms2/include"
      ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
        'OTHER_LDFLAGS': ['-stdlib=libc++'],
      },
      "libraries" : [
        "${PWD}/deps/ffms2/src/index/ffmsindex.cpp"
      ],
    }],
    ['OS=="linux"', {
      "cflags" : [
        "-g",
        "-D__STDC_CONSTANT_MACROS",
        "-D_FILE_OFFSET_BITS=64",
        "-D_LARGEFILE_SOURCE",
        "-O3",
        "-Wall"
      ],
      "libraries" : [
        "-lavcodec"
      ]
    }],
    ['OS=="win"', {
      "include_dirs": [
        "$(LIBAV_PATH)include"
      ],
      "libraries" : [
        "-l$(LIBAV_PATH)avcodec",
        "-l$(LIBAV_PATH)avformat",
        "-l$(LIBAV_PATH)swscale",
        "-l$(LIBAV_PATH)avresample",
        "-l$(LIBAV_PATH)avutil"
      ]
    }]
  ],
}]
}
