void bufoverflow()
{
    char buf[64];

    gets(buf); /* Here is the stack buffer overflow bug */
    return;
}