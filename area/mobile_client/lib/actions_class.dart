class Actions {
  Actions({
    required this.name,
    required this.description,
    required this.serviceName,
  });
  final String name;
  final String description;
  final String serviceName;

  factory Actions.fromJson(Map<String, dynamic> data) {
    final name = data['name'] as String;
    final description = data['description'] as String;
    final serviceName = data['serviceName'] as String;
    return Actions(name: name, description: description, serviceName: serviceName);
  }
}
