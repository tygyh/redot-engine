/**************************************************************************/
/*  vset.h                                                                */
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

#include "core/templates/vector.h"
#include "core/typedefs.h"

template <typename T>
class VSet {
	Vector<T> _data;

protected:
	_FORCE_INLINE_ int _find(const T &p_val, bool &r_exact) const {
		r_exact = false;
		if (_data.is_empty()) {
			return 0;
		}

		int64_t pos = _data.span().bisect(p_val, true);

		if (pos < _data.size() && !(p_val < _data[pos]) && !(_data[pos] < p_val)) {
			r_exact = true;
		}
		return pos;
	}

	_FORCE_INLINE_ int _find_exact(const T &p_val) const {
		if (_data.is_empty()) {
			return -1;
		}

		int64_t pos = _data.span().bisect(p_val, true);

		if (pos < _data.size() && !(p_val < _data[pos]) && !(_data[pos] < p_val)) {
			return pos;
		}
		return -1;
	}

public:
	void insert(const T &p_val) {
		bool exact;
		int pos = _find(p_val, exact);
		if (exact) {
			return;
		}
		_data.insert(pos, p_val);
	}

	bool has(const T &p_val) const {
		return _find_exact(p_val) != -1;
	}

	void erase(const T &p_val) {
		int pos = _find_exact(p_val);
		if (pos < 0) {
			return;
		}
		_data.remove_at(pos);
	}

	int find(const T &p_val) const {
		return _find_exact(p_val);
	}

	_FORCE_INLINE_ bool is_empty() const { return _data.is_empty(); }

	_FORCE_INLINE_ int size() const { return _data.size(); }

	inline T &operator[](int p_index) {
		return _data.write[p_index];
	}

	inline const T &operator[](int p_index) const {
		return _data[p_index];
	}

	_FORCE_INLINE_ VSet() {}
	_FORCE_INLINE_ VSet(std::initializer_list<T> p_init) :
			_data(p_init) {}
};
