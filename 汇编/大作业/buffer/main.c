#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define BUF_SIZE    16

#define CHR_CR		0x0D
#define CHR_ESC		0x1B
#define CHR_HL		'-'

typedef struct buffer *BUFFER;
struct buffer {
    char data[BUF_SIZE];
    int  head;
    int  tail;
    int  nsize;
};


static char outBuffer(BUFFER buf)
{
    char tc;
    if (buf->nsize) {
        tc = buf->data[buf->head];
        buf->head++;
        buf->nsize--;
        if (buf->head >= BUF_SIZE)
            buf->head = 0;
        return tc;
    } else {
        return '\0';
    }
}

static char insBuffer(BUFFER buf, char e)
{
    if (buf->nsize == BUF_SIZE) {
        return '\0';
    } else {
        buf->data[buf->tail] = e;
        buf->tail++;
        buf->nsize++;
        if (buf->tail >= BUF_SIZE)
            buf->tail = 0;
        return e;
    }
}


int main()
{
    int k, c;

    BUFFER smpbuf = (BUFFER)malloc(sizeof(struct buffer));
    smpbuf->head = 0;
    smpbuf->tail = 0;
    smpbuf->nsize = 0;

	printf("Please input any word between 0-9 or a-z or A-Z,and press - to get element out of queue,press Esc to exit:\n");

	while (CHR_ESC != (k = _getche())) {
		if (CHR_HL == k) {
			if (c = outBuffer(smpbuf))
				printf("\t get element %c out of queue\n", c);
			else
				printf("\tThe queue is empty\n");
		} else if ((k >= '0' && k <= '9') || (k >= 'A' && k <= 'Z')|| (k >= 'a' && k <= 'z')) {
			if (insBuffer(smpbuf, k))
				printf("\t put element %c into queue\n", k);
			else
				printf("\tThe queue is full\n");
		} else {
			putchar('\r');
		}
	}
	return 0;
}
