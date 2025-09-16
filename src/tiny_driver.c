
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tiny_driver.h"

ty_driver_t *ty_driver_init(const ty_device_t *device[]) {
  uint32_t num = 0;
  while ((device[num] != NULL) && (num <= UINT8_MAX)) {
    num += 1;
  }
  if (num > UINT8_MAX) {
    goto __ty_driver_too_many_devices;
  }

  ty_driver_t *dri = (ty_driver_t *)malloc(sizeof(ty_driver_t));
  if (dri == NULL) {
    goto __ty_driver_failed_to_malloc_0;
  }
  ty_status_t *status = (ty_status_t *)malloc(sizeof(ty_status_t) * num);
  if (status == NULL) {
    goto __ty_driver_failed_to_malloc_1;
  }
  for (int i = 0; i < num; i++) {
    status[i].is_opened = false;
  }
  // status[STDIN_FILENO].is_opened = false;
  status[STDOUT_FILENO].is_opened = true;
  status[STDERR_FILENO].is_opened = true;

  dri->device = device;
  dri->device_num = num;
  dri->status = status;

  return dri;
__ty_driver_failed_to_malloc_1:
  free((void *)dri);
__ty_driver_failed_to_malloc_0:
__ty_driver_too_many_devices:
  return NULL;
}

int ty_driver_open(ty_driver_t *dri, const char *name, int flags, int mode) {
  int fd = -1;
  for (int i = 0; dri->device[i] != NULL; i++) {
    if (strcmp(dri->device[i]->name, name) == 0) {
      fd = i;
      break;
    }
  }
  if (fd == -1) {
    errno = ENODEV;
    return -1;
  }
  if (dri->status[fd].is_opened) {
    errno = EBUSY;
    return -1;
  }
  if (dri->device[fd]->open_fn == NULL) {
    errno = ENOSYS;
    return -1;
  }
  if (dri->device[fd]->open_fn(name, flags, mode) >= 0) {
    dri->status[fd].is_opened = true;
    return fd;
  }
  return -1;
}

int ty_driver_close(ty_driver_t *dri, int fd) {
  if (fd >= dri->device_num) {
    errno = ENODEV;
    return -1;
  }
  if (!(dri->status[fd].is_opened)) {
    return 0;
  }
  if (dri->device[fd]->close_fn == NULL) {
    errno = ENOSYS;
    return -1;
  }
  if (dri->device[fd]->close_fn() >= 0) {
    dri->status[fd].is_opened = false;
    return 0;
  }
  return -1;
}

int ty_driver_write(ty_driver_t *dri, int fd, const void *buf, int len) {
  if (fd >= dri->device_num) {
    errno = ENODEV;
    return -1;
  }
  if (!(dri->status[fd].is_opened)) {
    errno = ENOENT;
    return -1;
  }
  if (dri->device[fd]->write_fn == NULL) {
    errno = ENOSYS;
    return -1;
  }
  return dri->device[fd]->write_fn(buf, len);
}

int ty_driver_read(ty_driver_t *dri, int fd, void *buf, int len) {
  if (fd >= dri->device_num) {
    errno = ENODEV;
    return -1;
  }
  if (!(dri->status[fd].is_opened)) {
    errno = ENOENT;
    return -1;
  }
  if (dri->device[fd]->read_fn == NULL) {
    errno = ENOSYS;
    return -1;
  }
  return dri->device[fd]->read_fn(buf, len);
}