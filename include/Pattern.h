/*
 * Pattern.h - declaration of class Pattern, which contains all information
 *             about a pattern
 *
 * Copyright (c) 2004-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of LMMS - http://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef PATTERN_H
#define PATTERN_H

#include <QtCore/QVector>
#include <QWidget>
#include <QDialog>
#include <QtCore/QThread>
#include <QPixmap>


#include "Note.h"
#include "Track.h"


class QAction;
class QProgressBar;
class QPushButton;

class InstrumentTrack;
class SampleBuffer;



class EXPORT Pattern : public TrackContentObject
{
	Q_OBJECT
public:
	enum PatternTypes
	{
		BeatPattern,
		MelodyPattern
	} ;

	Pattern( InstrumentTrack* instrumentTrack );
	Pattern( const Pattern& other );
	virtual ~Pattern();

	void init();


	virtual MidiTime length() const;
	MidiTime beatPatternLength() const;

	// note management
	Note * addNote( const Note & _new_note, const bool _quant_pos = true );

	void removeNote( const Note * _note_to_del );

	Note * noteAtStep( int _step );

	Note * rearrangeNote( const Note * _note_to_proc,
						const bool _quant_pos = true );
	void rearrangeAllNotes();
	void clearNotes();

	inline const NoteVector & notes() const
	{
		return m_notes;
	}

	void setStep( int _step, bool _enabled );

	// pattern-type stuff
	inline PatternTypes type() const
	{
		return m_patternType;
	}
	void setType( PatternTypes _new_pattern_type );
	void checkType();


	// next/previous track based on position in the containing track
	Pattern * previousPattern() const;
	Pattern * nextPattern() const;

	// settings-management
	virtual void saveSettings( QDomDocument & _doc, QDomElement & _parent );
	virtual void loadSettings( const QDomElement & _this );
	inline virtual QString nodeName() const
	{
		return "pattern";
	}

	inline InstrumentTrack * instrumentTrack() const
	{
		return m_instrumentTrack;
	}

	bool empty();


	virtual TrackContentObjectView * createView( TrackView * _tv );


	using Model::dataChanged;


protected:
	void ensureBeatNotes();
	void updateBBTrack();


protected slots:
	void addSteps();
	void cloneSteps();
	void removeSteps();
	void clear();
	void changeTimeSignature();


private:
	InstrumentTrack * m_instrumentTrack;

	PatternTypes m_patternType;

	// data-stuff
	NoteVector m_notes;
	int m_steps;

	Pattern * adjacentPatternByOffset(int offset) const;

	friend class PatternView;
	friend class BBTrackContainerView;


signals:
	void destroyedPattern( Pattern* );

} ;



class PatternView : public TrackContentObjectView
{
	Q_OBJECT

// theming qproperties
	Q_PROPERTY( QColor fgColor READ fgColor WRITE setFgColor )
	Q_PROPERTY( QColor textColor READ textColor WRITE setTextColor )
public:
	PatternView( Pattern* pattern, TrackView* parent );
	virtual ~PatternView();


public slots:
	virtual void update();


protected slots:
	void openInPianoRoll();

	void resetName();
	void changeName();


protected:
	virtual void constructContextMenu( QMenu * );
	virtual void mousePressEvent( QMouseEvent * _me );
	virtual void mouseDoubleClickEvent( QMouseEvent * _me );
	virtual void paintEvent( QPaintEvent * _pe );
	virtual void resizeEvent( QResizeEvent * _re )
	{
		m_needsUpdate = true;
		TrackContentObjectView::resizeEvent( _re );
	}
	virtual void wheelEvent( QWheelEvent * _we );


private:
	static QPixmap * s_stepBtnOn;
	static QPixmap * s_stepBtnOverlay;
	static QPixmap * s_stepBtnOff;
	static QPixmap * s_stepBtnOffLight;

	Pattern* m_pat;
	QPixmap m_paintPixmap;
	bool m_needsUpdate;
} ;



#endif
