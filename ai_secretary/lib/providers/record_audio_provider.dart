import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:record/record.dart';
import 'package:ai_converter/services/permission_management.dart';
import 'package:ai_converter/services/storage_management.dart';
import 'package:ai_converter/services/toast_services.dart';
import 'package:http/http.dart' as http;

class RecordAudioProvider extends ChangeNotifier {
  String _fileId = ''; // Add this line to declare _fileId
  final Record _record = Record();
  bool _isRecording = false;
  String _afterRecordingFilePath = '';
  Map<String, dynamic>? _apiResponse;
  Map<String, dynamic>? get apiResponse => _apiResponse;

  bool get isRecording => _isRecording;
  String get recordedFilePath => _afterRecordingFilePath;

  clearOldData() {
    _afterRecordingFilePath = '';
    notifyListeners();
  }

  recordVoice() async {
    final _isPermitted = (await PermissionManagement.recordingPermission()) &&
        (await PermissionManagement.storagePermission());

    if (!_isPermitted) return;

    if (!(await _record.hasPermission())) return;

    final _voiceDirPath = await StorageManagement.getAudioDir;
    final _voiceFilePath = StorageManagement.createRecordAudioPath(
        dirPath: _voiceDirPath, fileName: 'audio_message');

    await _record.start(path: _voiceFilePath);
    _isRecording = true;
    notifyListeners();

    showToast('Recording Started');
  }

  Future<void> stopRecording() async {
    String? _audioFilePath;

    if (await _record.isRecording()) {
      _audioFilePath = await _record.stop();
      showToast('Recording Stopped');
    }

    print('Audio file path: $_audioFilePath');

    _isRecording = false;
    _afterRecordingFilePath = _audioFilePath ?? '';
    notifyListeners();

    if (_afterRecordingFilePath.isNotEmpty) {
      _fileId = await uploadAudioFile(_afterRecordingFilePath);
      final secondApiResponse = await callSecondApi(_fileId);
      print('Second API response: $secondApiResponse');
      _apiResponse = secondApiResponse;
      notifyListeners();
    }
  }

  Future<Map<String, dynamic>> callSecondApi(String fileId) async {
    try {
      var request = http.MultipartRequest(
        'GET',
        Uri.parse('https://whisper.yang-lin.dev/api/process/$fileId'),
      );

      request.fields['file_id'] = fileId;

      var response = await request.send();

      if (response.statusCode == 200) {
        final jsonResponse = await response.stream.bytesToString();
        try {
          final Map<String, dynamic> decodedJson = jsonDecode(jsonResponse);
          return decodedJson;
        } catch (e) {
          print('Error parsing second API response from JSON: $e');
          print('JSON response: $jsonResponse');
          throw Exception('Failed to parse second API response');
        }
      } else {
        print('Failed to call second API. Status code: ${response.statusCode}');
        throw Exception('Failed to call second API');
      }
    } catch (error) {
      print('Error calling second API: $error');
      rethrow;
    }
  }

  Future<String> uploadAudioFile(String filePath) async {
    try {
      var request = http.MultipartRequest(
        'POST',
        Uri.parse('https://whisper.yang-lin.dev/api/upload'),
      );

      request.files.add(
        await http.MultipartFile.fromPath('file', filePath),
      );

      var response = await request.send();

      if (response.statusCode == 200) {
        final jsonResponse = await response.stream.bytesToString();
        try {
          final Map<String, dynamic> decodedJson = jsonDecode(jsonResponse);
          final fileId = decodedJson['file_id'] as String;
          final status = decodedJson['status'] as String;

          print('First API Response: $fileId, status: $status');
          return fileId; // Return fileId
        } catch (e) {
          print('Error parsing album from JSON: $e');
          print('JSON response: $jsonResponse');
          rethrow;
        }
      } else {
        print(
            'Failed to upload audio file. Status code: ${response.statusCode}');
        throw Exception('Failed to upload audio file');
      }
    } catch (error) {
      print('Error uploading audio file: $error');
      rethrow;
    }
  }
}
