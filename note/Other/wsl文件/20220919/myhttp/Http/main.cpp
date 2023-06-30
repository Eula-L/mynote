#include <iostream>
#include <cstring>
// #include "SysInfo.h"
#include "HttpRequest.h"
 
int main() {
    // std::cout << SysInfo::getEndian() << std::endl;
    char response[65535] = {'\0'};
    HttpRequest request;
    int ret = request.get(response, "www.bilibili.com", "/api/sendCode", "124.239.244.15");
#if 1
    //int ret = request.post(response, "api.????.com", "/v1/app/send_verify_code",
           //                "???.??.10.204", "phone=???????9242&phone_cc=86&tag=CppTest");
#endif
    std::cout << "errno=" << ret << " " << strerror(ret) << "\r\n";
    std::cout << "========\r\n";
    std::cout << response << std::endl;
 
    return 0;
}
