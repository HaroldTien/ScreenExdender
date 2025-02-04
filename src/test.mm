#import <Foundation/Foundation.h>

#define TOKEN 2

int (^power)(int, int) = ^(int a, int b) {
    return a * b;
};


int main() {
    CGFloat product = (CGFloat)pow(2, 3);
    NSLog(@"product = %f", product);
    return 0;
}