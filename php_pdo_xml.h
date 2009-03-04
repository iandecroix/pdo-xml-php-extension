/*
 * PdoXml main
 * Copyright (c) 2008, SOFTPAE.com
 *
 * This file is part of PdoXml.
 *
 * PdoXml is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * PdoXml is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with PdoXml; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* $ Id: $ */ 

#ifndef PHP_PDO_XML_H
#define PHP_PDO_XML_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_PDO_XML

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>

#include "zend_API.h"
//#include "../ext/simplexml/php_simplexml_exports.h"
#include "../ext/standard/php_smart_str.h"
#include "../ext/standard/html.h"

#ifdef  __cplusplus
} // extern "C" 
#endif
#ifdef  __cplusplus
extern "C" {
#endif

zend_class_entry*		g_ClassEntry;
zend_object_handlers	g_ClassHandlers; 

extern zend_module_entry pdo_xml_module_entry;
#define phpext_pdo_xml_ptr &pdo_xml_module_entry

#ifdef PHP_WIN32
#define PHP_PDO_XML_API __declspec(dllexport)
#else
#define PHP_PDO_XML_API
#endif

PHP_MINIT_FUNCTION(pdo_xml);
PHP_MSHUTDOWN_FUNCTION(pdo_xml);
PHP_RINIT_FUNCTION(pdo_xml);
PHP_RSHUTDOWN_FUNCTION(pdo_xml);
PHP_MINFO_FUNCTION(pdo_xml);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_HAVE_PDO_XML */

#endif /* PHP_PDO_XML_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
