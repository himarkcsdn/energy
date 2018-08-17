#include<stdio.h>

//计数器
int my_strlen(const char* str)
{
	int count = 0;
	while (*str)
	{
		str++; //地址++
		count++;
	}
	return count;
}

//指针实现
int my_strlen1(const char* str)
{
	char* p = str;
	while (*p != '\0')
		p++;
	return p - str;
}

char* my_strcpy(char* dest, const char* src)
{
	assert(dest != NULL);
	assert(src != NULL);
	char* ret = dest;
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}

char* mystrcat(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest != NULL);
	assert(src != NULL);
	while (*dest)
		dest++;
	while (*dest++ = *src++)
		;
	return ret;
}

char* mystrstr(const char* str1, const char* str2)
{
	assert(str1);
	assert(str2);

	char* start = (char*)str1;
	char* substr = (char*)str2;
	char* cp = (char*)str1;   

	if (*str2 == '\0')
	{
		return NULL;
	}

	while (*cp)//cp保存首地址
	{
		start = cp;
		substr = str2;
		while (*start && *substr && (*start == *substr))
		{
			start++;
			substr++;
		}
		if (*substr == '\0')
			return cp;
		cp++;
	}

}

int mystrcmp(const char* str1, const char* str2)
{
	int ret = 0;
	assert(str1);
	assert(str2);

	while (!(ret = *(unsigned*)str1 - *(unsigned char*)str2) && *str2)
	{
		++str1;
		++str2;
	}
	if (ret < 0)
		ret = -1;
	else if (ret>0)
		ret = 1;
	else
		ret = 0;
	return ret;
}

void* memcpy(void* dest, const void* src, size_t count)
{
	void* ret = dest;

	while (count--)
	{
		*(char*)dest = *(char*)src;
		dest = (char*)dest + 1;
		src = (char*)src + 1;
	}
	return (ret);
}

