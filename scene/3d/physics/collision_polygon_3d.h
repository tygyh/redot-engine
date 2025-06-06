/**************************************************************************/
/*  collision_polygon_3d.h                                                */
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

#include "scene/3d/node_3d.h"

class CollisionObject3D;
class CollisionPolygon3D : public Node3D {
	GDCLASS(CollisionPolygon3D, Node3D);
	real_t margin = 0.04;

protected:
	real_t depth = 1.0;
	AABB aabb = AABB(Vector3(-1, -1, -1), Vector3(2, 2, 2));
	Vector<Point2> polygon;

	uint32_t owner_id = 0;
	CollisionObject3D *collision_object = nullptr;

	Color debug_color;
	bool debug_fill = true;

	Color _get_default_debug_color() const;

	bool disabled = false;

	void _build_polygon();

	void _update_in_shape_owner(bool p_xform_only = false);

	bool _is_editable_3d_polygon() const;

protected:
	void _notification(int p_what);
	static void _bind_methods();

#ifdef DEBUG_ENABLED
	bool _property_can_revert(const StringName &p_name) const;
	bool _property_get_revert(const StringName &p_name, Variant &r_property) const;
	void _validate_property(PropertyInfo &p_property) const;
#endif // DEBUG_ENABLED

public:
	void set_depth(real_t p_depth);
	real_t get_depth() const;

	void set_polygon(const Vector<Point2> &p_polygon);
	Vector<Point2> get_polygon() const;

	void set_disabled(bool p_disabled);
	bool is_disabled() const;

	void set_debug_color(const Color &p_color);
	Color get_debug_color() const;

	void set_debug_fill_enabled(bool p_enable);
	bool get_debug_fill_enabled() const;

	virtual AABB get_item_rect() const;

	real_t get_margin() const;
	void set_margin(real_t p_margin);

	PackedStringArray get_configuration_warnings() const override;

	CollisionPolygon3D();
};
