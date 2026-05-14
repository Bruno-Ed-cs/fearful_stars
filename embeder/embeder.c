#include <stdio.h>
#include <raylib.h>

int main(int argc, char** argv) {

    for (int i = 1; i < argc; i++) {

        printf("arg: %s\n", argv[i]);

        if (!FileExists(argv[i])) {
            printf("File: %s not found\n", argv[i]);
            continue;
        }
        const char* file_name = GetFileName(argv[i]);
        const char* file_name_clean = GetFileNameWithoutExt(argv[i]);
        int file_len = 0; 

        unsigned char* data = LoadFileData(argv[i], &file_len);

        int file_name_len = TextLength(file_name_clean);
        const char* extension = ".h";
        char* file_name_final = TextInsert(file_name_clean, extension, file_name_len);

        if (!ExportDataAsCode(data, file_len, file_name_final)) {

            printf("Exporting of file %s failed\n", argv[1]);
        }

        UnloadFileData(data);
    }

    return 0;

}
