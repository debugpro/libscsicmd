#include "scsicmd.h"

#include <stdio.h>
#include <string.h>

bool parse_inquiry(char *buf, unsigned buf_len, int *device_type, scsi_vendor_t vendor, scsi_model_t model,
                   scsi_fw_revision_t revision, scsi_serial_t serial)
{
        *device_type = -1;
        vendor[0] = 0;
        model[0] = 0;
        revision[0] = 0;
        serial[0] = 0;

        if (buf_len < 44)
                return false;

        unsigned char fmt = buf[3] & 0xf; 
        if (fmt != 2 && fmt != 1) {
                fprintf(stderr, "Data not in standard format (%d but expected 2)\n", fmt);
                return false;
        }

        int valid_len = buf[4] + 4;

        *device_type = buf[0] & 0x1f;

        if (valid_len >= 8 + SCSI_VENDOR_LEN) {
                strncpy(vendor, (char*)buf+8, SCSI_VENDOR_LEN);
                vendor[SCSI_VENDOR_LEN] = 0;
        }

        if (valid_len >= 16 + SCSI_MODEL_LEN) {
                strncpy(model, (char*)buf+16, SCSI_MODEL_LEN);
                model[SCSI_MODEL_LEN] = 0;
        }

        if (valid_len >= 32 + SCSI_FW_REVISION_LEN) {
                strncpy(revision, (char*)buf+32, SCSI_FW_REVISION_LEN);
                revision[SCSI_FW_REVISION_LEN] = 0;
        }

        if (valid_len >= 44 && fmt == 2) {
                strncpy(serial, (char*)buf+36, SCSI_SERIAL_LEN);
                serial[SCSI_SERIAL_LEN] = 0;
        }

        return true;
}