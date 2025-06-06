/**************************************************************************/
/*  node_dock.h                                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             REDOT ENGINE                               */
/*                        https://redotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2024-present Redot Engine contributors                   */
/*                                          (see REDOT_AUTHORS.md)        */
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#include "groups_editor.h"

class ConfigFile;
class ConnectionsDock;

class NodeDock : public VBoxContainer {
	GDCLASS(NodeDock, VBoxContainer);

	Button *connections_button = nullptr;
	Button *groups_button = nullptr;

	ConnectionsDock *connections = nullptr;
	GroupsEditor *groups = nullptr;

	HBoxContainer *mode_hb = nullptr;

	Label *select_a_node = nullptr;

	void _save_layout_to_config(Ref<ConfigFile> p_layout, const String &p_section) const;
	void _load_layout_from_config(Ref<ConfigFile> p_layout, const String &p_section);

private:
	inline static NodeDock *singleton = nullptr;

public:
	static NodeDock *get_singleton() { return singleton; }

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	void set_node(Node *p_node);

	void show_groups();
	void show_connections();

	void update_lists();

	NodeDock();
	~NodeDock();
};
