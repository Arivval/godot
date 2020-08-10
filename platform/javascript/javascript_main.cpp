/*************************************************************************/
/*  javascript_main.cpp                                                  */
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

#include "core/io/resource_loader.h"
#include "main/main.h"
#include "platform/javascript/os_javascript.h"

#include <emscripten/emscripten.h>

<<<<<<< HEAD
static OS_JavaScript *os = nullptr;
=======
static OS_JavaScript *os = NULL;
static uint64_t target_ticks = 0;

// Files drop (implemented in JS for now).
extern "C" EMSCRIPTEN_KEEPALIVE void _drop_files_callback(char *p_filev[], int p_filec) {
	if (!os || !os->get_main_loop()) {
		ERR_FAIL_MSG("Unable to drop files because the OS or MainLoop are not active");
	}
	Vector<String> files;
	for (int i = 0; i < p_filec; i++) {
		files.push_back(String::utf8(p_filev[i]));
	}
	os->get_main_loop()->drop_files(files);
}
>>>>>>> amandotjain/pad_publishing

void exit_callback() {
	emscripten_cancel_main_loop(); // After this, we can exit!
	Main::cleanup();
	int exit_code = OS_JavaScript::get_singleton()->get_exit_code();
	memdelete(os);
<<<<<<< HEAD
	os = nullptr;
=======
	os = NULL;
>>>>>>> amandotjain/pad_publishing
	emscripten_force_exit(exit_code); // No matter that we call cancel_main_loop, regular "exit" will not work, forcing.
}

void main_loop_callback() {
<<<<<<< HEAD
	if (os->main_loop_iterate()) {
		emscripten_cancel_main_loop(); // Cancel current loop and wait for finalize_async.
		EM_ASM({
			// This will contain the list of operations that need to complete before cleanup.
			Module.async_finish = [];
		});
=======
	uint64_t current_ticks = os->get_ticks_usec();

	bool force_draw = os->check_size_force_redraw();
	if (force_draw) {
		Main::force_redraw();
	} else if (current_ticks < target_ticks && !force_draw) {
		return; // Skip frame.
	}

	int target_fps = Engine::get_singleton()->get_target_fps();
	if (target_fps > 0) {
		target_ticks += (uint64_t)(1000000 / target_fps);
	}
	if (os->main_loop_iterate()) {
		emscripten_cancel_main_loop(); // Cancel current loop and wait for finalize_async.
		/* clang-format off */
		EM_ASM({
			// This will contain the list of operations that need to complete before cleanup.
			Module.async_finish = [
				// Always contains at least one async promise, to avoid firing immediately if nothing is added.
				new Promise(function(accept, reject) {
					setTimeout(accept, 0);
				})
			];
		});
		/* clang-format on */
>>>>>>> amandotjain/pad_publishing
		os->get_main_loop()->finish();
		os->finalize_async(); // Will add all the async finish functions.
		EM_ASM({
			Promise.all(Module.async_finish).then(function() {
				Module.async_finish = [];
				ccall("cleanup_after_sync", null, []);
			});
		});
	}
}
<<<<<<< HEAD

extern "C" EMSCRIPTEN_KEEPALIVE void cleanup_after_sync() {
	emscripten_set_main_loop(exit_callback, -1, false);
}

extern "C" EMSCRIPTEN_KEEPALIVE void main_after_fs_sync(char *p_idbfs_err) {
=======

extern "C" EMSCRIPTEN_KEEPALIVE void cleanup_after_sync() {
	emscripten_set_main_loop(exit_callback, -1, false);
}

extern "C" EMSCRIPTEN_KEEPALIVE void main_after_fs_sync(char *p_idbfs_err) {
	// Set IDBFS status
>>>>>>> amandotjain/pad_publishing
	String idbfs_err = String::utf8(p_idbfs_err);
	if (!idbfs_err.empty()) {
		print_line("IndexedDB not available: " + idbfs_err);
	}
	os->set_idb_available(idbfs_err.empty());
<<<<<<< HEAD
	// TODO: Check error return value.
	Main::setup2(); // Manual second phase.
=======

	// Set canvas ID
	char canvas_ptr[256];
	/* clang-format off */
	EM_ASM({
		stringToUTF8("#" + Module['canvas'].id, $0, 255);
	}, canvas_ptr);
	/* clang-format on */
	os->canvas_id.parse_utf8(canvas_ptr, 255);

	// Set locale
	char locale_ptr[16];
	/* clang-format off */
	EM_ASM({
		stringToUTF8(Module['locale'], $0, 16);
	}, locale_ptr);
	/* clang-format on */
	setenv("LANG", locale_ptr, true);

	Main::setup2();
>>>>>>> amandotjain/pad_publishing
	// Ease up compatibility.
	ResourceLoader::set_abort_on_missing_resources(false);
	Main::start();
	os->get_main_loop()->init();
<<<<<<< HEAD
	emscripten_resume_main_loop();
	// Immediately run the first iteration.
	// We are inside an animation frame, we want to immediately draw on the newly setup canvas.
	main_loop_callback();
}

int main(int argc, char *argv[]) {
	os = new OS_JavaScript();
=======
	// Immediately run the first iteration.
	// We are inside an animation frame, we want to immediately draw on the newly setup canvas.
	main_loop_callback();
	emscripten_resume_main_loop();
}

int main(int argc, char *argv[]) {
	// Create and mount userfs immediately.
	EM_ASM({
		FS.mkdir('/userfs');
		FS.mount(IDBFS, {}, '/userfs');
	});
	os = new OS_JavaScript(argc, argv);
>>>>>>> amandotjain/pad_publishing
	Main::setup(argv[0], argc - 1, &argv[1], false);
	emscripten_set_main_loop(main_loop_callback, -1, false);
	emscripten_pause_main_loop(); // Will need to wait for FS sync.

	// Sync from persistent state into memory and then
	// run the 'main_after_fs_sync' function.
	/* clang-format off */
	EM_ASM({
<<<<<<< HEAD
		FS.mkdir('/userfs');
		FS.mount(IDBFS, {}, '/userfs');
=======
>>>>>>> amandotjain/pad_publishing
		FS.syncfs(true, function(err) {
			requestAnimationFrame(function() {
				ccall('main_after_fs_sync', null, ['string'], [err ? err.message : ""]);
			});
		});
	});
	/* clang-format on */

	return 0;
	// Continued async in main_after_fs_sync() from the syncfs() callback.
}
