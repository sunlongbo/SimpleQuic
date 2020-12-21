// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <Foundation/Foundation.h>


// A block, that takes a request, and returns YES if the request should
// be handled.
typedef BOOL (^RequestFilterBlock)(NSURLRequest* request);

__attribute__((visibility("default")))
@interface Cronet : NSObject

// Sets the HTTP Accept-Language header.  This method only has any effect before
// |start| is called.
+ (void)setAcceptLanguages:(NSString*)acceptLanguages;


// Set experimental Cronet options.  Argument is a JSON string; see
// |URLRequestContextConfig| for more details.  This method only has
// any effect before |start| is called.
+ (void)setExperimentalOptions:(NSString*)experimentalOptions;

// Sets the User-Agent request header string to be sent with all requests.
// If |partial| is set to YES, then actual user agent value is based on device
// model, OS version, and |userAgent| argument. For example "Foo/3.0.0.0" is
// sent as "Mozilla/5.0 (iPhone; CPU iPhone OS 9_3 like Mac OS X)
// AppleWebKit/601.1 (KHTML, like Gecko) Foo/3.0.0.0 Mobile/15G31
// Safari/601.1.46".
// If |partial| is set to NO, then |userAgent| value is complete value sent to
// the remote. For Example: "Foo/3.0.0.0" is sent as "Foo/3.0.0.0".
//
// This method only has any effect before |start| is called.
+ (void)setUserAgent:(NSString*)userAgent partial:(BOOL)partial;


// Sets the block used to determine whether or not Cronet should handle the
// request. If the block is not set, Cronet will handle all requests. Cronet
// retains strong reference to the block, which can be released by calling this
// method with nil block.
+ (void)setRequestFilterBlock:(RequestFilterBlock)block;

// Starts CronetEngine. It is recommended to call this method on the application
// main thread. If the method is called on any thread other than the main one,
// the method will internally try to execute synchronously using the main GCD
// queue. Please make sure that the main thread is not blocked by a job
// that calls this method; otherwise, a deadlock can occur.
+ (void)start;

// Registers Cronet as HttpProtocol Handler. Once registered, Cronet intercepts
// and handles all requests made through NSURLConnection and shared
// NSURLSession.
// This method must be called after |start|.
+ (void)registerHttpProtocolHandler;

// Unregister Cronet as HttpProtocol Handler. This means that Cronet will stop
// intercepting requests, however, it won't tear down the Cronet environment.
// This method must be called after |start|.
+ (void)unregisterHttpProtocolHandler;

// Installs Cronet into NSURLSessionConfiguration so that all
// NSURLSessions created with this configuration will use the Cronet stack.
// Note that all Cronet settings are global and are shared between
// all NSURLSessions & NSURLConnections that use the Cronet stack.
// This method must be called after |start|.
+ (void)installIntoSessionConfiguration:(NSURLSessionConfiguration*)config;


// Returns the full user-agent that will be used unless it is overridden on the
// NSURLRequest used.
+ (NSString*)getUserAgent;

// Sets priority of the network thread. The |priority| should be a
// floating point number between 0.0 to 1.0, where 1.0 is highest priority.
// This method can be called multiple times before or after |start| method.
+ (void)setNetworkThreadPriority:(double)priority;



@end
