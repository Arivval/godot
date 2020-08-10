/*************************************************************************/
/*  os_javascript.h                                                      */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef OS_JAVASCRIPT_H
#define OS_JAVASCRIPT_H

#include "audio_driver_javascript.h"
#include "core/input/input.h"
#include "drivers/unix/os_unix.h"
#include "servers/audio_server.h"

#include <emscripten/html5.h>

class OS_JavaScript : public OS_Unix {
<<<<<<< HEAD
	MainLoop *main_loop = nullptr;
	AudioDriverJavaScript audio_driver_javascript;
=======

	VideoMode video_mode;
	Vector2 windowed_size;
	bool window_maximized;
	bool entering_fullscreen;
	bool just_exited_fullscreen;
	bool transparency_enabled;

	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE webgl_ctx;

	InputDefault *input;
	Ref<InputEventKey> deferred_key_event;
	CursorShape cursor_shape;
	String cursors[CURSOR_MAX];
	Map<CursorShape, Vector<Variant> > cursors_cache;
	Point2 touches[32];

	Point2i last_click_pos;
	double last_click_ms;
	int last_click_button_index;

	int last_width;
	int last_height;

	MainLoop *main_loop;
	int video_driver_index;
	AudioDriverJavaScript *audio_driver_javascript;
	VisualServer *visual_server;
>>>>>>> amandotjain/pad_publishing

	bool finalizing = false;
	bool idb_available = false;
	int64_t sync_wait_time = -1;
	int64_t last_sync_check_time = -1;

	static void file_access_close_callback(const String &p_file, int p_flags);

protected:
<<<<<<< HEAD
	virtual void initialize();
=======
	void resume_audio();

	virtual int get_current_video_driver() const;

	virtual void initialize_core();
	virtual Error initialize(const VideoMode &p_desired, int p_video_driver, int p_audio_driver);
>>>>>>> amandotjain/pad_publishing

	virtual void set_main_loop(MainLoop *p_main_loop);
	virtual void delete_main_loop();

	virtual void finalize();

	virtual bool _check_internal_feature_support(const String &p_feature);

public:
	String canvas_id;
	void finalize_async();
	bool check_size_force_redraw();

	// Override return type to make writing static callbacks less tedious.
	static OS_JavaScript *get_singleton();

<<<<<<< HEAD
	virtual void initialize_joypads();
=======
	virtual void swap_buffers();
	virtual void set_video_mode(const VideoMode &p_video_mode, int p_screen = 0);
	virtual VideoMode get_video_mode(int p_screen = 0) const;
	virtual void get_fullscreen_mode_list(List<VideoMode> *p_list, int p_screen = 0) const;

	virtual void set_window_size(const Size2);
	virtual Size2 get_window_size() const;
	virtual void set_window_maximized(bool p_enabled);
	virtual bool is_window_maximized() const;
	virtual void set_window_fullscreen(bool p_enabled);
	virtual bool is_window_fullscreen() const;
	virtual Size2 get_screen_size(int p_screen = -1) const;

	virtual Point2 get_mouse_position() const;
	virtual int get_mouse_button_state() const;
	virtual void set_cursor_shape(CursorShape p_shape);
	virtual void set_custom_mouse_cursor(const RES &p_cursor, CursorShape p_shape, const Vector2 &p_hotspot);
	virtual void set_mouse_mode(MouseMode p_mode);
	virtual MouseMode get_mouse_mode() const;
>>>>>>> amandotjain/pad_publishing

	virtual bool get_window_per_pixel_transparency_enabled() const;
	virtual void set_window_per_pixel_transparency_enabled(bool p_enabled);

	virtual bool has_touchscreen_ui_hint() const;

	virtual int get_audio_driver_count() const;
	virtual const char *get_audio_driver_name(int p_driver) const;

	virtual MainLoop *get_main_loop() const;
<<<<<<< HEAD
	void finalize_async();
=======
>>>>>>> amandotjain/pad_publishing
	bool main_loop_iterate();

	virtual Error execute(const String &p_path, const List<String> &p_arguments, bool p_blocking = true, ProcessID *r_child_id = nullptr, String *r_pipe = nullptr, int *r_exitcode = nullptr, bool read_stderr = false, Mutex *p_pipe_mutex = nullptr);
	virtual Error kill(const ProcessID &p_pid);
	virtual int get_process_id() const;

	String get_executable_path() const;
	virtual Error shell_open(String p_uri);
	virtual String get_name() const;
	virtual void add_frame_delay(bool p_can_draw) {}
	virtual bool can_draw() const;

	virtual String get_cache_path() const;
	virtual String get_config_path() const;
	virtual String get_data_path() const;
	virtual String get_user_data_dir() const;

	void set_idb_available(bool p_idb_available);
	virtual bool is_userfs_persistent() const;

	void resume_audio();
	bool is_finalizing() { return finalizing; }

	OS_JavaScript();
};

#endif
