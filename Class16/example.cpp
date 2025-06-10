#include <memory>
#include <cstdio>
#include <iostream>

void ProcessFile() {
   std::unique_ptr<FILE, int(*)(FILE*)> filePrt(fopen("notes.txt", "r"), fclose);
   if(!filePrt) {
       throw std::runtime_error("Failed to open file");
       return;
   }

   // Move ownerhip of filePrt to another unique_ptr
   auto process = [](std::unique_ptr<FILE, int(*)(FILE*)> file) {
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file.get())) {
            std::cout << buffer;
        }
        std::cout<<std::endl;
   };

   process(std::move(filePrt));
   // filePrt is now empty, and the file is closed automatically
}

int main() {
    ProcessFile();
    return 0;
}