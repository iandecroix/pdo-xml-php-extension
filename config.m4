dnl
dnl $ Id: $
dnl

PHP_ARG_ENABLE(pdo_xml, whether to enable pdo_xml functions,
[  --enable-pdo_xml         Enable pdo_xml support])

if test "$PHP_PDO_XML" != "no"; then
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $INCLUDES -DHAVE_PDO_XML"

  AC_MSG_CHECKING(PHP version)
  AC_TRY_COMPILE([#include <php_version.h>], [
#if PHP_VERSION_ID < 40000
#error  this extension requires at least PHP version 4.0.0
#endif
],
[AC_MSG_RESULT(ok)],
[AC_MSG_ERROR([need at least PHP 4.0.0])])

  export CPPFLAGS="$OLD_CPPFLAGS"


  PHP_SUBST(PDO_XML_SHARED_LIBADD)
  AC_DEFINE(HAVE_PDO_XML, 1, [ ])

  PHP_NEW_EXTENSION(pdo_xml, pdo_xml.c , $ext_shared)

fi

