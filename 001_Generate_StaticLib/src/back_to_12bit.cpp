#include "b.h"
#include <stdint.h>

size_t find_file_size(FILE *f)
{
    size_t size;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

int convert_file(int frame_num)
{
    FILE *input_raw, *output;
    size_t file_size;
    int i;
    uint8_t *new_file;
    uint8_t *raw_file;
	char hdr_str[20];
    char fname[FILENAME_MAX];
    char fname2[FILENAME_MAX];
    sprintf(fname, "./Pic/NTUST_Xavier_test_%03u.raw", (unsigned)frame_num);
    sprintf(fname2, "./Pic_Convert/NTUST_Xavier_test_%03u.raw", (unsigned)frame_num);
    input_raw = fopen(fname, "rb");
    if (input_raw == NULL)
    {
        printf("Input raw is Null, return\n");
        return -1;
    }
    file_size = find_file_size(input_raw);

    new_file = (uint8_t *)malloc(file_size);
    raw_file = (uint8_t *)malloc(file_size);

    memset(new_file, 0, file_size);

    // Ignore 16 bytes header
    fseek(input_raw, 16, SEEK_SET);
    fread(raw_file, file_size, 1, input_raw);
    i = 0;
    for (i = 0; i < file_size; i += 2)
    {
        new_file[i] = ((raw_file[i + 1] & 0x0f) << 4) | (raw_file[i] >> 4);
        new_file[i + 1] = 0 | (raw_file[i + 1] >> 4);
    }
    // printf("new file[i] and new file[i+1]:\n");
    // printf("     0x%x            0x%x     \n", new_file[i],new_file[i+1]);
    output = fopen(fname2, "wb");

    if (output == NULL)
    {
        printf("output is Null, return\n");
        goto end;
    }

    fseek(output, 0, SEEK_SET);
    fseek(input_raw, 0, SEEK_SET);
    fread(hdr_str, 16, 1, input_raw);
    fwrite(hdr_str, 1, 16, output);
    fwrite(new_file, file_size, 1, output);

end:
    free(new_file);
    free(raw_file);
    fclose(input_raw);
    fclose(output);
    return 0;
}
