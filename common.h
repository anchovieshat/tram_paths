#define true 1
#define false 0

#if defined(DEBUG_FLAG) && DEBUG_FLAG == 2
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, __FILE__, __LINE__, __func__, ##args)
#elif defined(DEBUG_FLAG) && DEBUG_FLAG == 1
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: " fmt, ##args)
#else
#define DEBUG_PRINT(fmt, args...)
#endif

typedef float f32;
typedef uint64_t u64;
typedef uint32_t u32;
typedef u32 bool;

#define BOOL_FMT(x) x ? "true" : "false"

typedef struct FloatWrapper {
	f32 f;
} FloatWrapper;

FloatWrapper *fw_init(f32 f) {
	FloatWrapper *fw = (FloatWrapper *)malloc(sizeof(FloatWrapper));
	fw->f = f;
	return fw;
}

void fw_free(FloatWrapper *fw) {
	free(fw);
}

typedef struct File {
	char *filename;
	char *string;
	u64 size;
} File;

File *read_file(char *filename) {
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("%s not found!\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	u64 length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *file_string = (char *)malloc(length + 1);
	length = fread(file_string, 1, length, file);
	file_string[length] = 0;

	fclose(file);

	File *f = (File *)malloc(sizeof(File));
	f->filename = filename;
	f->string = file_string;
	f->size = length;

	return f;
}

char *file_to_string(const char *filename) {
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		printf("%s not found!\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	u64 length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *file_string = (char *)malloc(length + 1);
	length = fread(file_string, 1, length, file);
	file_string[length] = 0;

	fclose(file);
	return file_string;
}

char *station_lookup(char *station, char *line) {
	char *lookup_str = calloc(strlen(station) + strlen(line) + 2, sizeof(char));
	strcat(lookup_str, station);
	strcat(lookup_str, "~");
	strcat(lookup_str, line);
	return lookup_str;
}
