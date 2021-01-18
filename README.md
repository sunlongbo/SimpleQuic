# SimpleQuic
Simple QUIC/Http3 implementation for iOS based on google Cronet

如果在iOS中使用http3/QUIC， 很多人会考虑google的CRONET，但是5.5M的动态库大小让本身就比较大的APP难以接受，CRONET库是google chrome的整个网络模块的实现，包含了 http1, http2/spdy, QUIC/http3 以及 brotli压缩，DNS解析，log，内存管理，线程管理，TLS，boringssl， HPKP（HTTP Public Key Pinning） 等很多额外的功能。这个库的目的是缩减CRONET库减少不必要的功能。目前已经减少到2.3M， 持续压缩优化中

1. Cronet.framework 是缩减后的CRONET动态库，可以直接嵌入工程使用
2. SimpleQUICTest 是测试demo，请求测试站点quic.roks, 如果是以QUIC的方式请求会打印出成功日志
3. static/Cronet.framework 是缩减后的静态库
