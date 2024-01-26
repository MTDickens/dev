#define malloc(size) my_malloc(size)
#define free(size) my_free(size)

void *my_malloc(int);
void my_free(void *);