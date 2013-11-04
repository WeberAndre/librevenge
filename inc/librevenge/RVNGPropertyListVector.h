/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2005 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2006 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://librevenge.sourceforge.net
 */

#ifndef RVNGPROPERTYLISTVECTOR_H
#define RVNGPROPERTYLISTVECTOR_H

#include "RVNGPropertyList.h"

class RVNGPropertyListVectorImpl;
class RVNGPropertyListVectorIterImpl;

class RVNGPropertyListVector
{
public:
	RVNGPropertyListVector(const RVNGPropertyListVector &);
	RVNGPropertyListVector();
	virtual ~RVNGPropertyListVector();
	void append(const RVNGPropertyList &elem);
	void append(const RVNGPropertyListVector &vec);
	unsigned long count() const;
	const RVNGPropertyList &operator[](unsigned long index) const;
	RVNGPropertyListVector &operator=(const RVNGPropertyListVector &vect);

	class Iter
	{
	public:
		Iter(const RVNGPropertyListVector &vect);
		virtual ~Iter();
		void rewind();
		bool next();
		bool last();
		const RVNGPropertyList &operator()() const;

	private:
		RVNGPropertyListVectorIterImpl *m_iterImpl;
		Iter(const Iter &);
		Iter &operator=(const Iter &);
	};

	friend class RVNGPropertyListVector::Iter;

private:
	RVNGPropertyListVectorImpl *m_impl;
};

#endif /* RVNGPROPERTYLISTVECTOR_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */