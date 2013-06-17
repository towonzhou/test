#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
using namespace std;
void insert_kv(char* str, int count) {
    char *p = strchr(str, '=');
    *p = '\0';
    stringstream ss;
    ss << count;
    cout << str + ss.str() << endl;
}

int main() {
    char repo_info[1024] = "";
    FILE* fp;

    if (!(fp = fopen("/etc/yum/repos.d/qomo.repo", "r"))) {
        fp = fopen("/etc/yum/repos.d/redflag.repo", "r");
    }

    if (fp) {
        char buf[1024];
        int count = 0;
        while(fgets(buf, sizeof buf - 1, fp) != NULL) {
            if (strstr(buf, "mirrorlist")) {
                strncpy(repo_info, buf, sizeof buf - 1);

                int len = strlen(repo_info);
                if (!len) {
                    return 0;
                }

                fgets(buf, sizeof buf - 1, fp);
                char *e = strchr(buf, '=') + 1;

                if ( *e == '1' ) {
                    char *p = strchr(repo_info, '?') + 1;
                    char *param = strtok(p, "&");
                    while (param) {
                        insert_kv(param, count);
                        param = strtok(NULL, "&");
                    }
                    ++count;
                }
            }
        }
        fclose(fp);
    }
}
