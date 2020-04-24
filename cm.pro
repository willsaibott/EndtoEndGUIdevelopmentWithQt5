TEMPLATE = subdirs

SUBDIRS += \
  GUI \
  cm-Tests \
  lib

!build_pass:message(cm project dir: $${PWD})

