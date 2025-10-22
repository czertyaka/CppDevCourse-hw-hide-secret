void check_and_change(char* const text, const char* const secret, const int shift)
{
    int i = 0;
    while (secret[i] != '\0')
    {
        if (secret[i] != text[i + shift])
        {
            return;
        }
        i++;
    }

    i = 0;
    while (secret[i] != '\0')
    {
        text[i + shift] = 'x';
        i++;
    }
}

void hide_secret(char* const text, const char* const secret)
{
    int i = 0;
    while (text[i] != '\0')
    {
        check_and_change(text, secret, ++i);
    }
}