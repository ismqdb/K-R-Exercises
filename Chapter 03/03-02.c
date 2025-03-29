#include <stdio.h>

void escape(char s[], char t[]) {
	int si = 0;
	int ti = 0;

	for (; t[ti] != '\0'; ti++, si++) {
		switch (t[ti]) {
			case '\a':
				s[si++] = '\\';
				s[si] = 'a';
				break;
			case '\b':
				s[si++] = '\\';
				s[si] = 'b';
				break;
			case '\e':
				s[si++] = '\\';
				s[si] = 'e';
				break;
			case '\f':
				s[si++] = '\\';
				s[si] = 'f';
				break;
			case '\n':
				s[si++] = '\\';
				s[si] = 'n';
				break;
			case '\r':
				s[si++] = '\\';
				s[si] = 'r';
				break;
			case '\t':
				s[si++] = '\\';
				s[si] = 't';
				break;
			case '\v':
				s[si++] = '\\';
				s[si] = 'v';
				break;
			case '\\':
				s[si++] = '\\';
				s[si] = '\\';
				break;
			case '\'':
				s[si++] = '\\';
				s[si] = '\'';
				break;
			case '\"':
				s[si++] = '\\';
				s[si] = '"';
				break;
			case '\?':
				s[si++] = '\\';
				s[si] = '?';
				break;
			default:
				s[si] = t[ti];
				break;
		}
	}

	s[si] = '\0';
}

void convert(char s[], char t[]) {
	unsigned si = 0, ti = 0;

	for (; t[ti] != '\0'; si++, ti++) {
		switch (t[ti]) {
		case '\a':
			s[si] = 'a';
			break;
		case '\b':
			s[si] = 'b';
			break;
		case '\e':
			s[si] = 'e';
			break;
		case '\f':
			s[si] = 'f';
			break;
		case '\n':
			s[si] = 'n';
			break;
		case '\r':
			s[si] = 'r';
			break;
		case '\t':
			s[si] = 't';
			break;
		case '\v':
			s[si] = 'v';
			break;
		case '\\':
			s[si] = '\\';
			break;
		case '\'':
			s[si] = '\'';
			break;
		case '\"':
			s[si] = '"';
			break;
		case '\?':
			s[si] = '?';
			break;
		default:
			s[si] = t[ti];
			break;
		}
	}

	s[si] = '\0';
}

int main() {
	char t[] = "\a\e\b\'\n\\\\\0";
	char s1[sizeof(t) / sizeof(t[0]) * 2];
	char s2[sizeof(t) / sizeof(t[0]) * 2];

	escape(s1, t);
	convert(s2, t);

	printf("%s\n", s1);
	printf("%s\n", s2);
	
	return 0;
}