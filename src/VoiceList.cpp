//
// Created by ly on 2023/11/2.
//
#include <string>
#include "vector"
std::vector<std::string> midiSoundNames = {
        "原声钢琴", "明亮原声钢琴", "电子钢琴", "古筝钢琴", "电子钢琴 1", "电子钢琴 2", "大键琴", "克拉维", "钢片琴", "钟琴",
        "音乐盒", "颤音琴", "马林巴琴", "木琴", "管钟", "杜尔西默琴", "拉杆风琴", "打击风琴", "摇滚风琴", "教堂风琴",
        "簧风琴", "手风琴", "口琴", "探戈手风琴", "尼龙吉他", "钢弦吉他", "爵士电吉他", "清音电吉他", "弱音电吉他",
        "加驰电吉他", "失真吉他", "吉他和声", "原声贝斯", "指弹电贝斯", "拨弦电贝斯", "无弦贝斯", "掌声贝斯",
        "拍掌贝斯", "合成贝斯 1", "合成贝斯 2", "小提琴", "中提琴", "大提琴", "低音提琴", "颤音弦乐",
        "拨弦弦乐", "管弦乐竖琴", "定音鼓", "合奏弦乐 1", "合奏弦乐 2", "合成弦乐 1", "合成弦乐 2", "合唱人声",
        "嘴哼声", "合成人声", "交响打击", "小号", "长号", "大号", "闷音小号", "法国号", "铜管组", "合成铜管 1",
        "合成铜管 2", "高音萨克斯", "次中音萨克斯", "中音萨克斯", "低音萨克斯", "双簧管", "英国管", "巴松管", "单簧管",
        "短笛", "长笛", "短笛", "排笛", "瓶吹", "尺八", "口哨", "陶笛", "合成音 1 (方波)", "合成音 2 (锯齿波)",
        "合成音 3 (风琴)", "合成音 4 (长音片)", "合成音 5 (夏朗琴)", "合成音 6 (声音)", "合成音 7 (五度)", "合成音 8 (贝斯 + 合成)",
        "合成音 1 (新世纪)", "合成音 2 (温暖)", "合成音 3 (多音乐器)", "合成音 4 (合唱)", "合成音 5 (弓弦)", "合成音 6 (金属)", "合成音 7 (光环)", "合成音 8 (扫掠)",
        "特效音 1 (雨)", "特效音 2 (电影音轨)", "特效音 3 (水晶)", "特效音 4 (大气)", "特效音 5 (明亮)", "特效音 6 (小妖精)", "特效音 7 (回声)", "特效音 8 (科幻)",
        "西塔尔", "班卓琴", "三味线", "箏", "卡林巴", "风笛", "小提琴", "山奈",
        "叮当铃", "阿哥哥", "钢鼓", "木块", "太鼓", "音乐桶鼓", "合成鼓", "反转钹", "吉他按弦噪音", "呼吸噪音",
        "海滩", "鸟鸣", "电话铃声", "直升机", "掌声", "枪声"
};
std::vector<std::string> midiSoundNamesEng = {
        "Acoustic Grand Piano", "Bright Acoustic Piano", "Electric Grand Piano",
        "Honky-tonk Piano", "Electric Piano 1", "Electric Piano 2", "Harpsichord",
        "Clavi", "Celesta", "Glockenspiel", "Music Box", "Vibraphone",
        "Marimba", "Xylophone", "Tubular Bells", "Dulcimer",
        "Drawbar Organ", "Percussive Organ", "Rock Organ", "Church Organ",
        "Reed Organ", "Accordion", "Harmonica", "Tango Accordion",
        "Acoustic Guitar (nylon)", "Acoustic Guitar (steel)", "Electric Guitar (jazz)", "Electric Guitar (clean)",
        "Electric Guitar (muted)", "Overdriven Guitar", "Distortion Guitar", "Guitar Harmonics",
        "Acoustic Bass", "Electric Bass (finger)", "Electric Bass (pick)", "Fretless Bass",
        "Slap Bass 1", "Slap Bass 2", "Synth Bass 1", "Synth Bass 2",
        "Violin", "Viola", "Cello", "Contrabass",
        "Tremolo Strings", "Pizzicato Strings", "Orchestral Harp", "Timpani",
        "String Ensemble 1", "String Ensemble 2", "SynthStrings 1", "SynthStrings 2",
        "Choir Aahs", "Voice Oohs", "Synth Voice", "Orchestra Hit",
        "Trumpet", "Trombone", "Tuba", "Muted Trumpet",
        "French Horn", "Brass Section", "SynthBrass 1", "SynthBrass 2",
        "Soprano Sax", "Alto Sax", "Tenor Sax", "Baritone Sax",
        "Oboe", "English Horn", "Bassoon", "Clarinet",
        "Piccolo", "Flute", "Recorder", "Pan Flute",
        "Blown Bottle", "Shakuhachi", "Whistle", "Ocarina",
        "Lead 1 (square)", "Lead 2 (sawtooth)", "Lead 3 (calliope)", "Lead 4 (chiff)",
        "Lead 5 (charang)", "Lead 6 (voice)", "Lead 7 (fifths)", "Lead 8 (bass + lead)",
        "Pad 1 (new age)", "Pad 2 (warm)", "Pad 3 (polysynth)", "Pad 4 (choir)",
        "Pad 5 (bowed)", "Pad 6 (metallic)", "Pad 7 (halo)", "Pad 8 (sweep)",
        "FX 1 (rain)", "FX 2 (soundtrack)", "FX 3 (crystal)", "FX 4 (atmosphere)",
        "FX 5 (brightness)", "FX 6 (goblins)", "FX 7 (echoes)", "FX 8 (sci-fi)",
        "Sitar", "Banjo", "Shamisen", "Koto",
        "Kalimba", "Bagpipe", "Fiddle", "Shanai",
        "Tinkle Bell", "Agogo", "Steel Drums", "Woodblock",
        "Taiko Drum", "Melodic Tom", "Synth Drum", "Reverse Cymbal",
        "Guitar Fret Noise", "Breath Noise", "Seashore", "Bird Tweet",
        "Telephone Ring", "Helicopter", "Applause", "Gunshot"
};
