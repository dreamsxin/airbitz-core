/**
 * @file
 * AirBitz Export Data function prototypes.
 *
 * See LICENSE for copy, modification, and use permissions
 *
 * @author See AUTHORS
 * @version 1.0
 */

#include "ABC.h"
#include "ABC_Util.h"


#ifndef ABC_Export_h
#define ABC_Export_h

/* Maxium size of CSV record and fields in characters */
#define ABC_CSV_MAX_REC_SZ  16384
#define ABC_CSV_MAX_FLD_SZ  4096

#define ABC_CSV_DFLT_DELIMITER "|"
#define ABC_CSV_ALT1_DELIMITER ","

#define ABC_CSV_REC_TERM_NAME "VER"
#define ABC_CSV_REC_TERM_VALUE "1"


#define ABC_CSV(type)    struct { \
                                      type ov[ABC_CSV_MAX_FLD_SZ]; \
                                      type qv[ABC_CSV_MAX_FLD_SZ]; \
                                      size_t os; \
                                      size_t qs; \
                                }

#define ABC_CSV_INIT(fld, src)  { \
                                  strncpy((fld).ov, src, ABC_CSV_MAX_FLD_SZ); \
                                  memset((fld).qv, 0, sizeof((fld).qv)); \
                                  (fld).os = strlen(src); \
                                  (fld).qs = 0; \
                                }

#define ABC_CSV_INIT2(fld, src, type) {\
                                        char _tmpXform[ABC_CSV_MAX_FLD_SZ]; \
                                        snprintf(_tmpXform,ABC_CSV_MAX_FLD_SZ,"%" type, src); \
                                        ABC_CSV_INIT(fld, _tmpXform); \
                                      }

#define ABC_CSV_FMT(v, d)       { \
                                  size_t _sz = 0; \
                                  _sz = csv_write(v.qv, sizeof(v.qv), v.ov, v.os); \
                                  v.qs = _sz; \
                                  ABC_ALLOC(d, v.qs+1+1); \
                                  snprintf(d, v.qs+1+1,"%s%s", v.qv, ABC_CSV_ALT1_DELIMITER); \
                                }


typedef ABC_CSV(char) tABC_CSV;


#ifdef __cplusplus
extern "C" {
#endif

    tABC_CC ABC_ExportFormatCsv(const char *szUserName,
                                const char *szPassword,
                                tABC_TxInfo **pTransactions,
                                unsigned int iTransactionCount,
                                char **szCsvData,
                                tABC_Error *pError);


#ifdef __cplusplus
}
#endif

#endif
