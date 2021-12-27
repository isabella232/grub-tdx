/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2022  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  EFI CC measurement support code.
 */

#include <grub/err.h>
#include <grub/i18n.h>
#include <grub/efi/api.h>
#include <grub/efi/efi.h>
#include <grub/efi/cc.h>
#include <grub/tpm.h>
#include <grub/mm.h>

static grub_efi_guid_t cc_measurement_guid = GRUB_EFI_CC_MEASUREMENT_PROTOCOL_GUID;

static inline grub_err_t
grub_efi_log_event_status (grub_efi_status_t status)
{
  switch (status)
    {
    case GRUB_EFI_SUCCESS:
      return 0;
    case GRUB_EFI_DEVICE_ERROR:
      return grub_error (GRUB_ERR_IO, N_("Command failed"));
    case GRUB_EFI_INVALID_PARAMETER:
      return grub_error (GRUB_ERR_BAD_ARGUMENT, N_("Invalid parameter"));
    case GRUB_EFI_BUFFER_TOO_SMALL:
      return grub_error (GRUB_ERR_BAD_ARGUMENT, N_("Output buffer too small"));
    case GRUB_EFI_NOT_FOUND:
      return grub_error (GRUB_ERR_UNKNOWN_DEVICE, N_("TPM unavailable"));
    default:
      return grub_error (GRUB_ERR_UNKNOWN_DEVICE, N_("Unknown TPM error"));
    }
}

grub_err_t
grub_cc_log_event (unsigned char *buf, grub_size_t size, grub_uint8_t pcr,
		   const char *description)
{
  grub_efi_cc_event_t *event;
  grub_efi_status_t status;
  grub_efi_cc_protocol_t *cc;
  grub_efi_cc_mr_index_t mr;

  cc = grub_efi_locate_protocol (&cc_measurement_guid, NULL);
  if (cc == NULL)
    return 0;

  status = efi_call_3 (cc->map_pcr_to_mr_index, cc, pcr, &mr);
  if (status != GRUB_EFI_SUCCESS)
    return grub_efi_log_event_status (status);

  event = grub_zalloc (sizeof (grub_efi_cc_event_t)
		       + grub_strlen (description) + 1);
  if (event == NULL)
    return grub_error (GRUB_ERR_OUT_OF_MEMORY,
		       N_ ("cannot allocate CC event buffer"));

  event->Header.HeaderSize = sizeof (grub_efi_cc_event_header_t);
  event->Header.HeaderVersion = GRUB_EFI_CC_EVENT_HEADER_VERSION;
  event->Header.MrIndex = mr;
  event->Header.EventType = EV_IPL;
  event->Size = sizeof (*event) - sizeof (event->Event)
		+ grub_strlen (description) + 1;
  grub_memcpy (event->Event, description, grub_strlen (description) + 1);

  status = efi_call_5 (cc->hash_log_extend_event, cc, 0,
		       (grub_efi_physical_address_t) buf,
		       (grub_efi_uint64_t) size, event);
  grub_free (event);

  return grub_efi_log_event_status (status);
}
