
extern char *getenv();

char *get_sessionid (void) {
	return (getenv("SESSIONID"));
}
