import 'package:webview_flutter/webview_flutter.dart';
import 'package:flutter/material.dart';
import 'dart:io';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'login_screen.dart';
import 'package:flutter/services.dart';
import 'end_session.dart';

class WebViewPage extends StatefulWidget {
  final String url;
  final String title;
  final bool comeFrom;
  const WebViewPage(
      {Key? key,
      required this.url,
      required this.title,
      required this.comeFrom})
      : super(key: key);

  @override
  State<WebViewPage> createState() => _WebViewPageState();
}

class _WebViewPageState extends State<WebViewPage> {
  late WebViewController controller;

  @override
  void initState() {
    super.initState();
    if (Platform.isAndroid) WebView.platform = SurfaceAndroidWebView();
  }

  Future<bool> execSigninOauths(Uri uri, bool comeFrom) async {
    Map<String, dynamic> _result = uri.queryParameters;
    Map<String, dynamic> _tmp = {};
    _result.forEach((key, value) {
      _tmp[key] = value;
    });
    if (!_tmp.containsKey('code')) {
      _tmp['code'] = 'null';
    }
    if (!_tmp.containsKey('scope')) {
      _tmp['scope'] = 'null';
    }
    if (!_tmp.containsKey('state')) {
      _tmp['state'] = 'null';
    }
    if (!_tmp.containsKey('oauth_token')) {
      _tmp['oauth_token'] = 'null';
    }
    if (!_tmp.containsKey('oauth_verifier')) {
      _tmp['oauth_verifier'] = 'null';
    }
    const start = "callback/";
    const end = "?";
    final startIndex = uri.toString().indexOf(start);
    final endIndex = uri.toString().indexOf(end, startIndex + start.length);
    final serviceName =
        uri.toString().substring(startIndex + start.length, endIndex);
    if (!comeFrom) {
      final response = await http.get(
        Uri.parse('http://10.0.2.2:8080/auth/callback/$serviceName?code=' +
            _tmp["code"] +
            '&scope=' +
            _tmp["scope"] +
            '&state=' +
            _tmp["state"] +
            '&oauth_token=' +
            _tmp["oauth_token"] +
            '&oauth_verifier=' +
            _tmp["oauth_verifier"]),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
      );
      if (response.statusCode == 200) {
        final data = await json.decode(response.body);
        String list = data['token'] as String;
        await storage.write(key: 'area-token', value: list);
        return (true);
      } else if (response.statusCode == 403) {
        EndSession(context);
        return (false);
      } else {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
          content: Text("An error occured, please try again"),
        ));
        return (false);
      }
    } else {
      final token = await storage.read(key: 'area-token');
      if (token == null) {
        return (false);
      }
      final response = await http.get(
        Uri.parse('http://10.0.2.2:8080/auth/callback/$serviceName?code=' +
            _tmp["code"] +
            '&scope=' +
            _tmp["scope"] +
            '&state=' +
            _tmp["state"] +
            '&oauth_token=' +
            _tmp["oauth_token"] +
            '&oauth_verifier=' +
            _tmp["oauth_verifier"]),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
          'authorization': 'Bearer $token',
        },
      );
      if (response.statusCode == 200) {
        return (true);
      } else if (response.statusCode == 403) {
        EndSession(context);
        return (false);
      } else {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(
          content: Text("An error occured, please try again"),
        ));
        return (false);
      }
    }
  }

  _loadHtmlFromAssets() async {
    String fileHtmlContents =
        await rootBundle.loadString("assets/redirect.html");
    controller.loadUrl(Uri.dataFromString(fileHtmlContents,
            mimeType: 'text/html', encoding: Encoding.getByName('utf-8'))
        .toString());
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          iconTheme: const IconThemeData(
            color: Colors.black,
          ),
          backgroundColor: Colors.white,
          centerTitle: true,
          title:
              Text(widget.title, style: const TextStyle(color: Colors.black)),
        ),
        body: Column(children: [
          Expanded(
              child: WebView(
            initialUrl: widget.url,
            javascriptMode: JavascriptMode.unrestricted,
            onWebViewCreated: (controller) {
              this.controller = controller;
            },
            onPageStarted: (url) async {
              if (url.startsWith("http://localhost:8081/")) {
                final uri = Uri.parse(url);
                _loadHtmlFromAssets();
                final response = await execSigninOauths(uri, widget.comeFrom);
                if (response && !widget.comeFrom) {
                  Navigator.of(context).pushNamedAndRemoveUntil(
                      '/', (Route<dynamic> route) => false);
                } else if (response && widget.comeFrom) {
                  Navigator.pop(context);
                } else {
                  Navigator.of(context).pushNamedAndRemoveUntil(
                      '/login', (Route<dynamic> route) => false);
                }
              }
            },
          ))
        ]));
  }
}
