/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __APP_LAYOUT_H__
#define __APP_LAYOUT_H__

#include <app.h>
#include <Elementary.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifndef LOG_TAG
#define LOG_TAG "systemcallapp"
#endif

#if !defined(PACKAGE)
#define PACKAGE "org.example.systemcallapp"
#endif

#define APP_VIEW_EDJ "opt/usr/apps/org.example.systemcallapp/res/app_view.edj"
#define ICON_DIR "opt/usr/apps/org.example.systemcallapp/res/images"

typedef struct appdata {
	Evas_Object *win;
	Evas_Object *conform;
	Evas_Object *nf;
} appdata_s;

void gettimeofday_syscall_cb(void *data, Evas_Object *obj, void *event_info);
void printhello_syscall_cb(void *data, Evas_Object *obj, void *event_info);

#endif /* __APP_LAYOUT_H__ */
