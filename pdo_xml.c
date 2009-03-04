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

#include "php_pdo_xml.h"

#if HAVE_PDO_XML

PHP_METHOD(PdoXml, __construct)
{

}

PHP_METHOD(PdoXml, makeXML)
{
    zval *arr, **data;
    HashTable *arr_hash;
    HashPosition pointer;

	smart_str xmlstring = {0};

	zval *retval_ptr;
	int array_count;

	char *str = NULL;
	int str_len = 0;
	zend_bool html_encode = 1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|bs", &arr, &html_encode, &str, &str_len) == FAILURE) {
        RETURN_NULL();
    }

    arr_hash = Z_ARRVAL_P(arr);
    array_count = zend_hash_num_elements(arr_hash);

	smart_str_appends(&xmlstring, "<?xml version=\"1.0\"?>\n");

	/*
	smart_str_appends(&xmlstring, "<data count=\"");
	smart_str_append_long(&xmlstring, array_count);
	smart_str_appends(&xmlstring, "\">");
	*/

	if (str != NULL)
	{
		smart_str_appends(&xmlstring, "<");
		smart_str_appends(&xmlstring, str);
		smart_str_appends(&xmlstring, ">");
	}
	else
	{
		smart_str_appends(&xmlstring, "<data>\n");
	}
	
	smart_str_appends(&xmlstring, "\n");

    //php_printf("The array passed contains %d elements ", array_count);

    for(zend_hash_internal_pointer_reset_ex(arr_hash, &pointer); zend_hash_get_current_data_ex(arr_hash, (void**) &data, &pointer) == SUCCESS; zend_hash_move_forward_ex(arr_hash, &pointer)) {

		zval **data_assoc;
		HashTable *arr_hash_assoc;
		HashPosition pointer_assoc;

		arr_hash_assoc = Z_ARRVAL_PP(data);

		smart_str_appends(&xmlstring, "<item>\n");

		for(zend_hash_internal_pointer_reset_ex(arr_hash_assoc, &pointer_assoc); zend_hash_get_current_data_ex(arr_hash_assoc, (void**) &data_assoc, &pointer_assoc) == SUCCESS; zend_hash_move_forward_ex(arr_hash_assoc, &pointer_assoc)) {

			zval temp;
			char *key;
			int key_len;
			long index;

			if (zend_hash_get_current_key_ex(arr_hash_assoc, &key, &key_len, &index, 0, &pointer_assoc) == HASH_KEY_IS_STRING) {
				
				temp = **data_assoc;
				zval_copy_ctor(&temp);
				convert_to_string(&temp);

				smart_str_appendc(&xmlstring, '<');
				smart_str_appends(&xmlstring, key);
				smart_str_appendc(&xmlstring, '>');
				//smart_str_appends(&xmlstring, "\n");

				if (html_encode == 1)
				{
					char *html;
					int len;
					char *hint_charset = NULL;
					int hint_charset_len = 0;
					long quote_style = ENT_QUOTES;
					zend_bool double_encode = 0;

					html = php_escape_html_entities_ex(Z_STRVAL(temp), Z_STRLEN(temp), &len, 0, quote_style, hint_charset, double_encode TSRMLS_CC);

					smart_str_appendl(&xmlstring, html, len);

				} else {

					smart_str_appendl(&xmlstring, Z_STRVAL(temp), Z_STRLEN(temp));

				}
				
				//smart_str_appendl(&xmlstring, Z_STRVAL(temp), Z_STRLEN(temp));
				//smart_str_appends(&xmlstring, "\n");
				
				smart_str_appendc(&xmlstring, '<');
				smart_str_appendc(&xmlstring, '/');
				smart_str_appends(&xmlstring, key);
				smart_str_appendc(&xmlstring, '>');
				smart_str_appends(&xmlstring, "\n");
				
				zval_dtor(&temp);

			} else {
				php_error_docref(NULL TSRMLS_CC, E_WARNING, "Passed argument is not associative array.");
				RETURN_FALSE;
			}
		}

		smart_str_appends(&xmlstring, "</item>\n");

	}

	if (str != NULL)
	{
		smart_str_appends(&xmlstring, "</");
		smart_str_appends(&xmlstring, str);
		smart_str_appends(&xmlstring, ">");
	}
	else
	{
		smart_str_appends(&xmlstring, "</data>\n");
	}

	smart_str_appends(&xmlstring, "\n");

	smart_str_0(&xmlstring);

	RETURN_STRING(xmlstring.c, 0);

	/*
	zval *assertion;
	char *myeval = NULL;
	myeval = Z_STRVAL_PP(&assertion);
	*/
}

zend_function_entry class_methods[] = {
	PHP_ME(PdoXml,__construct,NULL, ZEND_ACC_CTOR|ZEND_ACC_PUBLIC)
	PHP_ME(PdoXml,makeXML,NULL, 0) 
	{NULL, NULL, NULL}
}; 

/* {{{ pdo_xml_functions[] */
function_entry pdo_xml_functions[] = {
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ pdo_xml_module_entry
 */
zend_module_entry pdo_xml_module_entry = {
	STANDARD_MODULE_HEADER,
	"pdo_xml",
	pdo_xml_functions,
	PHP_MINIT(pdo_xml),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(pdo_xml), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(pdo_xml),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(pdo_xml), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(pdo_xml),
	"0.0.1", 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PDO_XML
ZEND_GET_MODULE(pdo_xml)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(pdo_xml)
{

	/* add your stuff here */
	
	zend_class_entry	stubClassEntry;

	INIT_CLASS_ENTRY(stubClassEntry,"PdoXml",class_methods);
	g_ClassEntry = zend_register_internal_class(&stubClassEntry TSRMLS_CC);
	
	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(pdo_xml)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(pdo_xml)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(pdo_xml)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(pdo_xml)
{
	php_info_print_box_start(0);
	php_printf("<p>PDO_XML extension by <a href=\"http://www.intuitive.sk\">Intuitive.sk</a> (SOFTPAE.com)</p>\n");
	php_printf("<p>See <a href=\"http://projects.intuitive.sk\">Project page</a></p>\n");
	php_printf("<p>Version 0.0.15devel (2008-10-19)</p>\n");
	php_info_print_box_end();
	/* add your stuff here */

}
/* }}} */

#endif /* HAVE_PDO_XML */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
