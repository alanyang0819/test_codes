import 'dart:async';
import 'dart:convert';

import 'package:http/http.dart' as http;

Future<Album> fetchAlbum() async {
  final response =
      await http.get(Uri.parse('https://whisper.yang-lin.dev/api/upload'));

  if (response.statusCode == 200) {
    print('Response body: ${response.body}');
    // If the server did return a 200 OK response,
    // then parse the JSON.
    final album =
        Album.fromJson(jsonDecode(response.body) as Map<String, dynamic>);
    final secondApiResponse = await callSecondApi(album.fileId);

    print('Second API response: $secondApiResponse');

    return album;
  } else {
    print('Failed to load album. Status code: ${response.statusCode}');
    // If the server did not return a 200 OK response,
    // then throw an exception.
    throw Exception('Failed to load album');
  }
}

Future<Map<String, dynamic>> callSecondApi(String fileId) async {
  final secondApiResponse = await http
      .get(Uri.parse('https://whisper.yang-lin.dev/api/process/$fileId'));

  if (secondApiResponse.statusCode == 200) {
    final secondApiResponseData =
        jsonDecode(secondApiResponse.body) as Map<String, dynamic>;
    return secondApiResponseData;
  } else {
    print(
        'Failed to call second API. Status code: ${secondApiResponse.statusCode}');
    throw Exception('Failed to call second API');
  }
}

class Album {
  final String fileId;
  final String status;

  const Album({
    required this.fileId,
    required this.status,
  });

  factory Album.fromJson(Map<String, dynamic> json) {
    try {
      return Album(
        fileId: json['file_id'] as String,
        status: json['status'] as String,
      );
    } catch (e) {
      print('Error parsing JSON: $e');
      print('JSON response: $json');
      throw FormatException('Failed to load album. Response: $json');
    }
  }

  get title => null;
}
