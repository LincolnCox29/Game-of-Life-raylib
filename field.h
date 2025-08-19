#define FIELD_SIZE 100
typedef char** Field;

#define IS_ALIVE(cell) (cell == 1)
#define ALIVE 1
#define DEAD 0

Field newField();
void freeField(Field field);
void drawField(Field field);
void nextField(Field field, Field buffer);
void changeCell(Field field);