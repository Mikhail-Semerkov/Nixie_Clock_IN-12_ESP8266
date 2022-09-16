#include "tcp_server.h"

#define MAX_SRV_CLIENTS 4

int Client_Connected = 0;
int Port = 4001;

WiFiServer server(Port);
WiFiClient serverClients[MAX_SRV_CLIENTS];


void check_tcp_client()
{
    uint8_t i;

    if (server.hasClient())
    {
        for (i = 0; i < MAX_SRV_CLIENTS; i++)
        {

            if (!serverClients[i] || !serverClients[i].connected())
            {
                if (serverClients[i])
                    serverClients[i].stop();
                serverClients[i] = server.available();
                Client_Connected = i + 1;
                Serial.print("New client: ");
                Serial.print(Client_Connected);
                Serial.println();
                break;
            }
        }

        if (i == MAX_SRV_CLIENTS)
        {
            WiFiClient serverClient = server.available();
            serverClient.stop();
            Serial.println("Connection rejected ");
        }
    }
}

void check_tcp_data()
{
    uint8_t i;

    for (i = 0; i < MAX_SRV_CLIENTS; i++)
    {
        if (serverClients[i] && serverClients[i].connected())
        {
            if (serverClients[i].available())
            {
                while (serverClients[i].available())
                    Serial.write(serverClients[i].read());
            }
        }
    }
}

void tcp_trace(const char *fmt, ...)
{
    char buf[1024] = {};
    va_list li;

    va_start(li, fmt);
    vsprintf(buf, fmt, li);
    va_end(li);

    for (uint8_t i = 0; i < MAX_SRV_CLIENTS; i++)
    {
        if (serverClients[i] && serverClients[i].connected())
        {
            serverClients[i].write((uint8_t *)buf, strlen(buf));

            // delay(1);
        }
    }
}

void tcp_server_init(void)
{
    server.begin();
    server.setNoDelay(true);
}

void loop_tcp_server(void)
{
    check_tcp_client();
    check_tcp_data();
}