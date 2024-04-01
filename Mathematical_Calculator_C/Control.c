#include "Control.h"
#include <string.h>
#include <ctype.h>
int format_control(const char* str)
{
	if (strlen(str) == 1)
	{
		if (isnum(str)) return 1;
		else if (!strcmp(str, "e")) return 1;
		return 0;
	}
	else if (strlen(str) >= 2 && isnum(str))
	{
		return 1;
	}
	else if (strlen(str) >= 2 && !isnum(str))
	{
		 if (isfunc(str)) { return 1; }
		if (!strcmp(str, "pi")) { return 1; }
		return 0;
	}
	return 0;
}
int isnum(const char* str)
{
	if (strlen(str) == 1)
		return isdigit(*str);
	while (*str)
	{
		if (!isdigit(*str++))
		{
			return 0;
		}
	}
	return 1;
}
int isfunc(const char* str)
{
	if (strstr(str, "log") || strstr(str, "ln") || strstr(str, "sgn") || strstr(str, "cos") || strstr(str, "sin") || strstr(str, "tan") || strstr(str, "cot") ||
		strstr(str, "acos") || strstr(str, "asin") || strstr(str, "atan") || strstr(str, "acot"))
	{
		
		if (strstr(str, "("))
		{
			return 1;
		}

	}
	else if (strstr(str, "!") || strstr(str, "^"))
	{
		if (isnum(str + 1)) return 1;
		return 0;
	}
	else if (strstr(str, "(") || strstr(str, ")"))
	{
		return 1;
	}
	return 0;
}



