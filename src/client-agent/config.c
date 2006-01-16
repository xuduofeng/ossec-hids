/*   $OSSEC, config.c, v0.1, 2005/04/01, Daniel B. Cid$   */

/* Copyright (C) 2005 Daniel B. Cid <dcid@ossec.net>
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */



#include "shared.h"

#include "os_xml/os_xml.h"
#include "os_regex/os_regex.h"
#include "os_net/os_net.h"

#include "agentd.h"


/* Relocated from config_op.c */

/* ClientConf v0.2, 2005/03/03
 * Read the config file (for the remote client)
 * v0.2: New OS_XML
 */ 
int ClientConf(char *cfgfile)
{
    OS_XML xml;

    /* XML definitions */
    char *(xml_client_ip[])={xml_client,"server-ip",NULL};
    char *(xml_client_port[])={xml_client, "port",NULL};

    if(OS_ReadXML(cfgfile,&xml) < 0)
    {
        merror("config_op (ossec-agent): XML error: %s",xml.err);
        return(OS_INVALID);
    }

    if(!OS_RootElementExist(&xml, xml_client))
    {
        merror("config_op (ossec-agent): No client configuration");
        OS_ClearXML(&xml);
        return(0);
    }

    /* will get only the first element */
    logr->port = OS_GetOneContentforElement(&xml,xml_client_port);
    logr->rip  = OS_GetOneContentforElement(&xml,xml_client_ip);
    if(logr->rip == NULL)
    {
        merror("ossec-agent: You need to specify the remote IP");
        OS_ClearXML(&xml);
        return(OS_CFGERR);
    }

    OS_ClearXML(&xml);
    return(1);
}


/* EOF */
