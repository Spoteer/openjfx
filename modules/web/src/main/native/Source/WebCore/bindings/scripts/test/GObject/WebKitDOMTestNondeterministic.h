/*
 *  This file is part of the WebKit open source project.
 *  This file has been generated by generate-bindings.pl. DO NOT MODIFY!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef WebKitDOMTestNondeterministic_h
#define WebKitDOMTestNondeterministic_h

#ifdef WEBKIT_DOM_USE_UNSTABLE_API

#include <glib-object.h>
#include <webkitdom/WebKitDOMObject.h>
#include <webkitdom/webkitdomdefines-unstable.h>

G_BEGIN_DECLS

#define WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC            (webkit_dom_test_nondeterministic_get_type())
#define WEBKIT_DOM_TEST_NONDETERMINISTIC(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC, WebKitDOMTestNondeterministic))
#define WEBKIT_DOM_TEST_NONDETERMINISTIC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC, WebKitDOMTestNondeterministicClass)
#define WEBKIT_DOM_IS_TEST_NONDETERMINISTIC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC))
#define WEBKIT_DOM_IS_TEST_NONDETERMINISTIC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC))
#define WEBKIT_DOM_TEST_NONDETERMINISTIC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj),  WEBKIT_DOM_TYPE_TEST_NONDETERMINISTIC, WebKitDOMTestNondeterministicClass))

struct _WebKitDOMTestNondeterministic {
    WebKitDOMObject parent_instance;
};

struct _WebKitDOMTestNondeterministicClass {
    WebKitDOMObjectClass parent_class;
};

WEBKIT_API GType
webkit_dom_test_nondeterministic_get_type(void);

/**
 * webkit_dom_test_nondeterministic_nondeterministic_zero_arg_function:
 * @self: A #WebKitDOMTestNondeterministic
 *
 * Returns: A #gboolean
 *
 * Stability: Unstable
**/
WEBKIT_API gboolean
webkit_dom_test_nondeterministic_nondeterministic_zero_arg_function(WebKitDOMTestNondeterministic* self);

/**
 * webkit_dom_test_nondeterministic_get_nondeterministic_readonly_attr:
 * @self: A #WebKitDOMTestNondeterministic
 *
 * Returns: A #glong
 *
 * Stability: Unstable
**/
WEBKIT_API glong
webkit_dom_test_nondeterministic_get_nondeterministic_readonly_attr(WebKitDOMTestNondeterministic* self);

/**
 * webkit_dom_test_nondeterministic_get_nondeterministic_writeable_attr:
 * @self: A #WebKitDOMTestNondeterministic
 *
 * Returns: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API gchar*
webkit_dom_test_nondeterministic_get_nondeterministic_writeable_attr(WebKitDOMTestNondeterministic* self);

/**
 * webkit_dom_test_nondeterministic_set_nondeterministic_writeable_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @value: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API void
webkit_dom_test_nondeterministic_set_nondeterministic_writeable_attr(WebKitDOMTestNondeterministic* self, const gchar* value);

/**
 * webkit_dom_test_nondeterministic_get_nondeterministic_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @error: #GError
 *
 * Returns: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API gchar*
webkit_dom_test_nondeterministic_get_nondeterministic_exception_attr(WebKitDOMTestNondeterministic* self, GError** error);

/**
 * webkit_dom_test_nondeterministic_set_nondeterministic_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @value: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API void
webkit_dom_test_nondeterministic_set_nondeterministic_exception_attr(WebKitDOMTestNondeterministic* self, const gchar* value);

/**
 * webkit_dom_test_nondeterministic_get_nondeterministic_getter_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @error: #GError
 *
 * Returns: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API gchar*
webkit_dom_test_nondeterministic_get_nondeterministic_getter_exception_attr(WebKitDOMTestNondeterministic* self, GError** error);

/**
 * webkit_dom_test_nondeterministic_set_nondeterministic_getter_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @value: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API void
webkit_dom_test_nondeterministic_set_nondeterministic_getter_exception_attr(WebKitDOMTestNondeterministic* self, const gchar* value);

/**
 * webkit_dom_test_nondeterministic_get_nondeterministic_setter_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 *
 * Returns: A #gchar
 *
 * Stability: Unstable
**/
WEBKIT_API gchar*
webkit_dom_test_nondeterministic_get_nondeterministic_setter_exception_attr(WebKitDOMTestNondeterministic* self);

/**
 * webkit_dom_test_nondeterministic_set_nondeterministic_setter_exception_attr:
 * @self: A #WebKitDOMTestNondeterministic
 * @value: A #gchar
 * @error: #GError
 *
 * Stability: Unstable
**/
WEBKIT_API void
webkit_dom_test_nondeterministic_set_nondeterministic_setter_exception_attr(WebKitDOMTestNondeterministic* self, const gchar* value, GError** error);

G_END_DECLS

#endif /* WEBKIT_DOM_USE_UNSTABLE_API */
#endif /* WebKitDOMTestNondeterministic_h */