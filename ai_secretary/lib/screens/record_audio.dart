import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_markdown/flutter_markdown.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';

import 'package:provider/provider.dart';

import 'package:ai_converter/providers/record_audio_provider.dart';
import 'package:simple_ripple_animation/simple_ripple_animation.dart';

class RecordAndPlayScreen extends StatefulWidget {
  const RecordAndPlayScreen({Key? key}) : super(key: key);

  @override
  State<RecordAndPlayScreen> createState() => _RecordAndPlayScreenState();
}

class _RecordAndPlayScreenState extends State<RecordAndPlayScreen> {
  customizeStatusAndNavigationBar() {
    SystemChrome.setSystemUIOverlayStyle(const SystemUiOverlayStyle(
        systemNavigationBarColor: Colors.white,
        statusBarColor: Colors.transparent,
        systemNavigationBarIconBrightness: Brightness.dark,
        statusBarBrightness: Brightness.light));
  }

  int currentPageIndex = 0;

  @override
  void initState() {
    customizeStatusAndNavigationBar();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color.fromARGB(255, 255, 255, 255),
      appBar: AppBar(
        backgroundColor: Colors.black38,
        title: const Text('AI converter'),
      ),
      body: _buildPageContent(),
      bottomNavigationBar: NavigationBar(
        onDestinationSelected: (int index) {
          setState(() {
            currentPageIndex = index;
          });
        },
        indicatorColor: Colors.amber,
        selectedIndex: currentPageIndex,
        destinations: const <Widget>[
          NavigationDestination(
            selectedIcon: Icon(Icons.keyboard_voice_rounded),
            icon: Icon(Icons.keyboard_voice_outlined),
            label: 'Record',
          ),
          NavigationDestination(
            selectedIcon: Icon(Icons.add_task),
            icon: Icon(Icons.add_task),
            label: 'Result',
          ),
        ],
      ),
    );
  }

  _buildPageContent() {
    if (currentPageIndex == 0) {
      return _homepage();
    } else if (currentPageIndex == 1) {
      return _aboutUsPage();
    }
  }

  _homepage() {
    return Container(
      width: MediaQuery.of(context).size.width,
      height: MediaQuery.of(context).size.height,
      decoration: const BoxDecoration(
        image: DecorationImage(
          fit: BoxFit.cover,
          image: NetworkImage(
              "https://w0.peakpx.com/wallpaper/403/183/HD-wallpaper-sound-beat-dark-gray-sound-wave.jpg"),
        ),
      ),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const SizedBox(height: 250),
          _recordingSection(),
          const SizedBox(height: 40),
        ],
      ),
    );
  }

  _recordingSection() {
    final _recordProvider = Provider.of<RecordAudioProvider>(context);

    return GestureDetector(
      onTap: () async {
        if (_recordProvider.isRecording) {
          await _recordProvider.stopRecording();
        } else {
          await _recordProvider.recordVoice();
        }
      },
      child: Container(
        width: 70,
        height: 70,
        padding: const EdgeInsets.all(10),
        decoration: BoxDecoration(
          color: _recordProvider.isRecording
              ? Colors.red
              : const Color(0xff4BB543),
          borderRadius: BorderRadius.circular(100),
        ),
        child: _recordProvider.isRecording
            ? const RippleAnimation(
                repeat: true,
                color: Colors.red,
                minRadius: 80,
                ripplesCount: 6,
                child: Icon(
                  Icons.stop,
                  color: Colors.white,
                  size: 30,
                ),
              )
            : const Icon(
                Icons.keyboard_voice_rounded,
                color: Colors.white,
                size: 30,
              ),
      ),
    );
  }
}

_aboutUsPage() {
  return Scaffold(
    backgroundColor: Colors.white,
    body: SingleChildScrollView(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.start,
        children: [
          Container(
            padding: const EdgeInsets.only(left: 16.0),
            alignment: Alignment.topLeft,
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                const SizedBox(height: 16),
                // Use the context parameter in Provider.of
                Consumer<RecordAudioProvider>(
                  builder: (context, recordProvider, _) {
                    // Display API response information
                    if (recordProvider.apiResponse != null) {
                      final whisperText =
                          recordProvider.apiResponse!['whisper_text'];

                      // Show notification when the result is displayed
                      _showNotification(whisperText);

                      return GestureDetector(
                        onLongPress: () {
                          // Copy to clipboard logic
                          Clipboard.setData(ClipboardData(text: whisperText));
                          ScaffoldMessenger.of(context).showSnackBar(
                            const SnackBar(
                              content: Text('Result copied to clipboard'),
                            ),
                          );
                        },
                        child: Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: [
                            SizedBox(
                              height: MediaQuery.of(context)
                                  .size
                                  .height, // Set a fixed height or adjust as needed
                              child: Markdown(
                                data: whisperText,
                                styleSheet: MarkdownStyleSheet(
                                  textAlign: WrapAlignment.start,
                                  h1: const TextStyle(fontSize: 32),
                                  h2: const TextStyle(fontSize: 24),
                                  h3: const TextStyle(fontSize: 20),
                                  h4: const TextStyle(fontSize: 18),
                                  h5: const TextStyle(fontSize: 16),
                                  h6: const TextStyle(fontSize: 14),
                                  p: const TextStyle(fontSize: 16),
                                  a: const TextStyle(
                                    color: Colors.black,
                                    decoration: TextDecoration.underline,
                                  ),
                                ),
                              ),
                            ),
                            const SizedBox(height: 16),
                            ElevatedButton(
                              onPressed: () {
                                // Copy to clipboard logic
                                Clipboard.setData(
                                  ClipboardData(text: whisperText),
                                );
                                ScaffoldMessenger.of(context).showSnackBar(
                                  const SnackBar(
                                    content: Text('Result copied to clipboard'),
                                  ),
                                );
                              },
                              child: const Text('Copy text'),
                            ),
                          ],
                        ),
                      );
                    } else {
                      return Container(); // Placeholder if no API response yet
                    }
                  },
                ),
              ],
            ),
          ),
        ],
      ),
    ),
  );
}

void _showNotification(String message) async {
  final FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin =
      FlutterLocalNotificationsPlugin();

  const AndroidNotificationDetails androidPlatformChannelSpecifics =
      AndroidNotificationDetails(
    'Audio Convertion',
    'AI Secretary',
    channelDescription: 'Audio to Text',
    importance: Importance.max,
    priority: Priority.high,
    showWhen: true,
  );

  const NotificationDetails platformChannelSpecifics =
      NotificationDetails(android: androidPlatformChannelSpecifics);

  await flutterLocalNotificationsPlugin.show(
    0,
    'Convertion successed! Come and See now!',
    message,
    platformChannelSpecifics,
  );
}
