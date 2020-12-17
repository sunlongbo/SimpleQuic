//
//  ViewController.m
//  SimpleQuicTest
//
//  Created by Logan on 2020/12/16.
//

#import "ViewController.h"
#import <Cronet/Cronet.h>
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [Cronet registerHttpProtocolHandler];
    [self sendQUICTestRequest];
}

- (void)sendQUICTestRequest{
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask* task = [session dataTaskWithURL:[NSURL URLWithString:@"https://quic.rocks:4433/"] completionHandler:^(NSData * _Nullable jsonData, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        NSString* responseStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
        NSLog(@"%@",responseStr);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            [self sendQUICTestRequest];
        });
    }];

    [task resume];
}

@end
