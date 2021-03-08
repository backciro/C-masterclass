#include "SKILIFT.h"

static int N;
static char buf[100];

SKI SKIget()
{
	SKI list;

	FILE *fp = fopen("./skilift.txt", "r");

	fscanf(fp, "%d", &N);
	list = malloc(N * sizeof(*list));

	for (int i = 0; i < N; i++) {
		fscanf(fp, "%s %d", buf, &list[i].time_interval);
		list[i].skiliftID = strdup(buf);
	}

	fclose(fp);
	return list;
}

bool authorize(int cardId, char* skiliftId, int time)
{
	int t_i, ltime;

	t_i = GETinterval(skiliftId, N);
	ltime = GETlastT(skiliftId, cardId);

	if (time - ltime >= t_i)
		return TRUE;

	else
		return FALSE;
}