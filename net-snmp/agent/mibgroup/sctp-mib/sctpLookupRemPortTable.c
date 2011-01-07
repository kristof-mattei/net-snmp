/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/table_container.h>
#include "sctpLookupRemPortTable.h"

static netsnmp_container *sctpLookupRemPortTable_container;

/** Initializes the sctpLookupRemPortTable module */
void
init_sctpLookupRemPortTable(void)
{
    /*
     * here we initialize all the tables we're planning on supporting 
     */
    initialize_table_sctpLookupRemPortTable();
}

void
shutdown_sctpLookupRemPortTable(void)
{
    sctpLookupRemPortTable_container_clear
        (sctpLookupRemPortTable_container);
}

/** Initialize the sctpLookupRemPortTable table by defining its contents and how it's structured */
void
initialize_table_sctpLookupRemPortTable(void)
{
    static oid      sctpLookupRemPortTable_oid[] =
        { 1, 3, 6, 1, 2, 1, 104, 1, 7 };
    size_t          sctpLookupRemPortTable_oid_len =
        OID_LENGTH(sctpLookupRemPortTable_oid);
    netsnmp_handler_registration *reg = NULL;
    netsnmp_mib_handler *handler = NULL;
    netsnmp_container *container = NULL;
    netsnmp_table_registration_info *table_info = NULL;

    reg =
        netsnmp_create_handler_registration("sctpLookupRemPortTable",
                                            sctpLookupRemPortTable_handler,
                                            sctpLookupRemPortTable_oid,
                                            sctpLookupRemPortTable_oid_len,
                                            HANDLER_CAN_RONLY);
    if (NULL == reg) {
        snmp_log(LOG_ERR,
                 "error creating handler registration for sctpLookupRemPortTable\n");
        goto bail;
    }

    container =
        netsnmp_container_find("sctpLookupRemPortTable:table_container");
    if (NULL == container) {
        snmp_log(LOG_ERR,
                 "error creating container for sctpLookupRemPortTable\n");
        goto bail;
    }
    sctpLookupRemPortTable_container = container;

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    if (NULL == table_info) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for sctpLookupRemPortTable\n");
        goto bail;
    }
    netsnmp_table_helper_add_indexes(table_info, ASN_UNSIGNED,  /* index: sctpAssocRemPort */
                                     ASN_UNSIGNED,      /* index: sctpAssocId */
                                     0);
    table_info->min_column = COLUMN_SCTPLOOKUPREMPORTSTARTTIME;
    table_info->max_column = COLUMN_SCTPLOOKUPREMPORTSTARTTIME;

    /*************************************************
     *
     * inject container_table helper
     */
    handler = netsnmp_container_table_handler_get(table_info, container,
                                                  TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    if (NULL == handler) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for sctpLookupRemPortTable\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,
                 "error injecting container_table handler for sctpLookupRemPortTable\n");
        goto bail;
    }
    handler = NULL;             /* reg has it, will reuse below */

    /*
     * register the table
     */
    if (SNMPERR_SUCCESS != netsnmp_register_table(reg, table_info)) {
        snmp_log(LOG_ERR,
                 "error registering table handler for sctpLookupRemPortTable\n");
        goto bail;
    }

    return;                     /* ok */

    /*
     * Some error occurred during registration. Clean up and bail.
     */
  bail:                        /* not ok */

    if (handler)
        netsnmp_handler_free(handler);


    if (container)
        CONTAINER_FREE(container);

    if (reg)
        netsnmp_handler_registration_free(reg);
}

/** handles requests for the sctpLookupRemPortTable table */
int
sctpLookupRemPortTable_handler(netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    sctpLookupRemPortTable_entry *table_entry;

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request = requests; request; request = request->next) {
            if (request->processed)
                continue;
            table_entry = (sctpLookupRemPortTable_entry *)
                netsnmp_container_table_extract_context(request);
            table_info = netsnmp_extract_table_info(request);
            if ((NULL == table_entry) || (NULL == table_info)) {
                snmp_log(LOG_ERR,
                         "could not extract table entry or info for sctpLookupRemPortTable\n");
                snmp_set_var_typed_value(request->requestvb,
                                         SNMP_ERR_GENERR, NULL, 0);
                continue;
            }

            switch (table_info->colnum) {
            case COLUMN_SCTPLOOKUPREMPORTSTARTTIME:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb,
                                           ASN_TIMETICKS,
                                           table_entry->sctpLookupRemPortStartTime);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

sctpLookupRemPortTable_entry *
sctpLookupRemPortTable_entry_create(void)
{
    sctpLookupRemPortTable_entry *entry =
        SNMP_MALLOC_TYPEDEF(sctpLookupRemPortTable_entry);
    if (entry != NULL) {
        entry->oid_index.len = SCTP_LOOKUP_REM_PORT_TABLE_INDEX_SIZE;
        entry->oid_index.oids = entry->oid_tmp;
    }

    return entry;
}

int
sctpLookupRemPortTable_entry_update_index(sctpLookupRemPortTable_entry *
                                          entry)
{
    netsnmp_variable_list var_sctpAssocRemPort;
    netsnmp_variable_list var_sctpAssocId;
    int             err = 0;

    /*
     * prepare the value to be converted 
     */
    memset(&var_sctpAssocRemPort, 0, sizeof(var_sctpAssocRemPort));
    var_sctpAssocRemPort.type = ASN_UNSIGNED;
    var_sctpAssocRemPort.next_variable = &var_sctpAssocId;
    snmp_set_var_value(&var_sctpAssocRemPort,
                       (u_char *) & entry->sctpAssocRemPort,
                       sizeof(entry->sctpAssocRemPort));

    memset(&var_sctpAssocId, 0, sizeof(var_sctpAssocId));
    var_sctpAssocId.type = ASN_UNSIGNED;
    var_sctpAssocId.next_variable = NULL;
    snmp_set_var_value(&var_sctpAssocId, (u_char *) & entry->sctpAssocId,
                       sizeof(entry->sctpAssocId));

    /*
     * convert it 
     */
    err =
        build_oid_noalloc(entry->oid_index.oids, entry->oid_index.len,
                          &entry->oid_index.len, NULL, 0,
                          &var_sctpAssocRemPort);
    if (err)
        snmp_log(LOG_ERR, "error %d converting index to oid\n", err);

    /*
     * release any memory allocated during the conversion 
     */
    snmp_reset_var_buffers(&var_sctpAssocRemPort);

    return err;
}

void
sctpLookupRemPortTable_entry_copy(sctpLookupRemPortTable_entry * from,
                                  sctpLookupRemPortTable_entry * to)
{
    memcpy(to, from, sizeof(sctpLookupRemPortTable_entry));
    to->oid_index.oids = to->oid_tmp;
}


void
sctpLookupRemPortTable_entry_free(sctpLookupRemPortTable_entry * entry)
{
    if (entry != NULL)
        SNMP_FREE(entry);
}

netsnmp_container *
sctpLookupRemPortTable_get_container(void)
{
    return sctpLookupRemPortTable_container;
}


static void
sctpLookupRemPortTable_entry_clear(void *what, void *magic)
{
    sctpLookupRemPortTable_entry_free(what);
}

void
sctpLookupRemPortTable_container_clear(netsnmp_container *container)
{
    CONTAINER_CLEAR(container, sctpLookupRemPortTable_entry_clear, NULL);
}
