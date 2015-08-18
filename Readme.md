Collaborative Music Thing
=========================

What is it?
-----------
The collaborative music thing will comprise of a server - for synthesizing, and synchronising music; and a client - for collecting input from a user and for configuring and controlling the server. Each client will represent one 'instrument' - an instrument being a collection of oscillator, envelope, and effect settings. The client/server architecture will be designed with the assumption that it will only be used over LAN. This way, we can focus on one-way communication from client to server and we can make assumptions about latency that otherwise would pose problems.

Depends on
--------------------------
- Fmod
- QT

Things we need
--------------
- Client-side
    - GUI
        Methods to configure various stages of an instrument (oscillator/envelope/effect) + something for visual feedback, so that it isn't just knobs and buttons.
    - Input
    - Networking system
        For sending configuration and note on/off packets to the server

- Server-side
    - Networking system
        For recieving configuration and note packets from clients
    - Synthesis pipeline


Instruments
-----------
- Can be monophonic (single-note, arpegiated chords) or polyphonic (chords)
    - Polyphonic instruments will require one oscillator/envelope pair per voice
    - Single-note monophic instruments have to deal with multiple keys still
        How are new presses handled
        - Stack-like: Last note played is note voiced, previous notes are re-voiced on key release
        - Scan from right: Always play the highest note
Stages:
- Input
    - Note priority
    - Arpeggiation
    - Chordiator?
- Oscillator
    - Frequency (tied to key)
        - FM / WoW
    - Waveform
        - Pulse width/Duty cycle
- Envelope
    - Attack/Decay/Sustain (tied to key)/Release
    - Amplitude/Volume
        - AM / tremolo
    - Trigger/Legato
        Is the envelope started again if a new key is hit?
        Or does the new note start where the last left off
- Effects
    - Reverb !
    - Delay
    - Chorus
    - Flanger
- Compressor

Idea
----
- If scale degrees are sent to the server instead of notes then scales can be set/changed globally
