/* -*- c++ -*- */
/*
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef GR_INSPECTOR_INSPECTOR_FAMFORM_H
#define GR_INSPECTOR_INSPECTOR_FAMFORM_H


#include <QTimer>
#include <QWidget>
#include <QtGui/QtGui>
#include <gnuradio/msg_queue.h>
#include <qwtplot3d/qwt3d_surfaceplot.h>
#include <qwtplot3d/qwt3d_function.h>
#include <gnuradio/io_signature.h>
#include "signal_marker.h"

namespace Qwt3D
{
    class Plot : public SurfacePlot
    {
    public:
        Plot();
    };

}


namespace gr
{

    namespace inspector
    {


        class fam_form : public QWidget
        {
            Q_OBJECT

        public:
            void set_axis_x(float start, float stop);
            void msg_received();
            void set_cfreq(float freq);
            void spawn_signal_selector();
            void add_msg_queue(float cfreq, float bandwidth);
            float freq_to_x(float freq);
            float x_to_freq(float x);
            
            void update(const float *d);
 
            Qwt3D::Plot * plot;

            void drawOverlay();
            fam_form(QWidget *parent);
            ~fam_form();

        private:

            enum markerType
            {
                NONE,
                LEFT,
                CENTER,
                RIGHT
            };

            int d_interval, d_fft_len, d_marker_count;
            int *d_rf_unit;
            bool *d_manual;
            std::vector<float> d_axis_x, d_axis_y;
            std::vector<double> *d_buffer;
            float d_max, d_min, d_cfreq, d_mouse_offset;
            double* d_freq;
            std::vector<std::vector<float> >* d_rf_map;
            markerType d_clicked_marker;

            QwtSymbol *d_symbol;
            QTimer *d_timer;
            QCheckBox* d_manual_cb;
            gr::msg_queue* d_msg_queue;

            gr::thread::mutex d_mutex;

        protected:
            void resizeEvent(QResizeEvent * event);

        public slots:
            //void refresh();
            //void manual_cb_clicked(int state);

        };

    }
}

#endif 
