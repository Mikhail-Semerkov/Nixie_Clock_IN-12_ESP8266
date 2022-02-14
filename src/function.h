String formatBytes(size_t bytes)
{
    if (bytes < 1024)
    {
        return String(bytes) + " B";
    }
    else if (bytes < (1024 * 1024))
    {
        return String(bytes / 1024.0) + " KB";
    }
    else if (bytes < (1024 * 1024 * 1024))
    {
        return String(bytes / 1024.0 / 1024.0) + " MB";
    }
    else
    {
        return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
    }
}

extern String HexToRGB(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}