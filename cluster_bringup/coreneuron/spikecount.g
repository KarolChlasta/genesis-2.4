/* Network-wide spike recording for VAnet2.
 *
 * VAnet2-batch.g records Vm from three cells only (middlecell, Redgecell,
 * LLcell). Two of those sit on the edge and the corner of the 2D grid, and
 * planarconnect makes connectivity distance-dependent, so edge cells receive
 * fewer inputs and fire far below the population mean -- they cannot be used
 * to estimate network activity.
 *
 * This attaches a spikehistory element to every spikegen in both layers, so
 * the total spike count is exact. It is for characterisation only: writing one
 * line per spike costs real time, so never enable this in a timing run.
 */

create spikehistory /spikeout
setfield /spikeout filename "spikes_all.txt" leave_open 1 ident_toggle 0

int sc_n
for (sc_n = 0; sc_n < {Ex_NX*Ex_NY}; sc_n = sc_n + 1)
    addmsg /Ex_layer/Ex_cell[{sc_n}]/soma/spike /spikeout SPIKESAVE
end
for (sc_n = 0; sc_n < {Inh_NX*Inh_NY}; sc_n = sc_n + 1)
    addmsg /Inh_layer/Inh_cell[{sc_n}]/soma/spike /spikeout SPIKESAVE
end
echo "spikecount: attached spikehistory to "{Ex_NX*Ex_NY + Inh_NX*Inh_NY}" spikegens"
