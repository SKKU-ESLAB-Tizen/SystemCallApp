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

#include "main.h"
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>

typedef struct syscall_data {
	Evas_Object *nf;
	Evas_Object *call_button;
} syscall_data_s;

static void syscall_scroller_del_cb(void *data, Evas *e, Evas_Object *obj,
		void *event_info) {
	syscall_data_s *ld = data;
	ld->nf = NULL;
	ld->call_button = NULL;
}

static void syscall_popup_button_clicked_cb(void *data, Evas_Object *obj,
		void *event_info) {
	Evas_Object *popup = data;
	evas_object_del(popup);
}

static Evas_Object *
create_syscall_popup(syscall_data_s *ld) {
	Evas_Object *popup, *button;

	Eina_Strbuf *buf = eina_strbuf_new();

	// Fill HERE!

	elm_object_text_set(popup, eina_strbuf_string_steal(buf));
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK,
			eext_popup_back_cb, NULL);
	elm_object_part_text_set(popup, "title,text", "gettimeofday system call");
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	button = elm_button_add(popup);
	elm_object_style_set(button, "popup");
	elm_object_text_set(button, "OK");
	elm_object_part_content_set(popup, "button1", button);
	evas_object_smart_callback_add(button, "clicked",
			syscall_popup_button_clicked_cb, popup);

	eina_strbuf_free(buf);

	return popup;
}

static Evas_Object *
create_input_field(Evas_Object *parent, syscall_data_s *ld) {
	Evas_Object *box, *label;

	box = elm_box_add(parent);

	label = elm_label_add(box);
	evas_object_size_hint_align_set(label, 0.05, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
	elm_box_pack_end(box, label);
	evas_object_show(label);

	return box;
}

static void syscall_cancel_button_clicked_cb(void *data, Evas_Object *obj,
		void *event_info) {
	syscall_data_s *ld = data;

	elm_naviframe_item_pop(ld->nf);
}

static void syscall_call_button_clicked_cb(void *data, Evas_Object *obj,
		void *event_info) {
	Evas_Object *popup;
	syscall_data_s *ld = data;

	popup = create_syscall_popup(ld);
	evas_object_show(popup);
}

static Evas_Object *
create_button_field(Evas_Object *parent, syscall_data_s *ld) {
	Evas_Object *box, *button;

	box = elm_box_add(parent);
	elm_box_horizontal_set(box, EINA_TRUE);
	elm_box_padding_set(box, ELM_SCALE_SIZE(10), 0);

	/* Cancel Button */
	button = elm_button_add(box);
	evas_object_size_hint_align_set(button, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, 0.0);
	evas_object_smart_callback_add(button, "clicked",
			syscall_cancel_button_clicked_cb, ld);
	elm_object_text_set(button, "Cancel");
	elm_box_pack_end(box, button);
	evas_object_show(button);

	/* syscall Button */
	ld->call_button = elm_button_add(box);
	evas_object_size_hint_align_set(ld->call_button, EVAS_HINT_FILL,
			EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(ld->call_button, EVAS_HINT_EXPAND, 0.0);
	evas_object_smart_callback_add(ld->call_button, "clicked",
			syscall_call_button_clicked_cb, ld);
	elm_object_text_set(ld->call_button, "Call");
//	elm_object_disabled_set(ld->call_button, EINA_TRUE);
	elm_box_pack_end(box, ld->call_button);
	evas_object_show(ld->call_button);

	return box;
}

void gettimeofday_syscall_cb(void *data, Evas_Object *obj, void *event_info) {
	appdata_s *ad = (appdata_s *) data;
	Evas_Object *scroller, *layout, *box;
	static syscall_data_s ld = { 0, };
	ld.nf = ad->nf;

	scroller = elm_scroller_add(ld.nf);
	evas_object_size_hint_align_set(scroller, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(scroller, EVAS_HINT_EXPAND, 0.0);
	evas_object_event_callback_add(scroller, EVAS_CALLBACK_DEL,
			syscall_scroller_del_cb, &ld);

	layout = elm_layout_add(scroller);
	elm_layout_file_set(layout, APP_VIEW_EDJ, "syscall_layout");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, 0.0);

	box = create_input_field(layout, &ld);
	elm_object_part_content_set(layout, "elm.swallow.content", box);

	box = create_button_field(layout, &ld);
	elm_object_part_content_set(layout, "elm.swallow.buttons", box);

	elm_object_content_set(scroller, layout);

	elm_naviframe_item_push(ld.nf, "Gettimeofday System Call", NULL, NULL, scroller,
			NULL);
}
