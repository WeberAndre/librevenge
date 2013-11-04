/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* librevenge
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2012 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef __RVNGSTRINGVECTOR_H__
#define __RVNGSTRINGVECTOR_H__

#include "RVNGString.h"

class RVNGStringVectorImpl;

class RVNGStringVector
{
public:
	RVNGStringVector();
	RVNGStringVector(const RVNGStringVector &vec);
	~RVNGStringVector();

	RVNGStringVector &operator=(const RVNGStringVector &vec);

	unsigned size() const;
	bool empty() const;
	const RVNGString &operator[](unsigned idx) const;
	void append(const RVNGString &str);
	void clear();

private:
	RVNGStringVectorImpl *m_pImpl;
};

#endif /* __RVNGSTRINGVECTOR_H__ */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */