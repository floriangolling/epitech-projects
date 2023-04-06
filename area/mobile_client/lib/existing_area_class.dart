class ExistingArea {
  final List<ExistingItems> existingItems;

  ExistingArea({
    required this.existingItems,
  });

  factory ExistingArea.fromJson(List<dynamic> parsedJson) {
    List<ExistingItems> existingItems = <ExistingItems>[];
    existingItems = parsedJson.map((i) => ExistingItems.fromJson(i)).toList();
    return ExistingArea(existingItems: existingItems);
  }
}

class ExistingItems {
  ExistingItems({
    required this.serviceActionName,
    required this.serviceReactionName,
    required this.actionName,
    required this.reactionName,
    required this.id,
    required this.state,
    required this.description,
  });
  final String serviceActionName;
  final String serviceReactionName;
  final String actionName;
  final String reactionName;
  final int id;
  final bool state;
  final String description;

  factory ExistingItems.fromJson(Map<String, dynamic> data) {
    final sActionName = data['serviceActionName'] as String?;
    if (sActionName == null) {
      throw UnsupportedError(
          'Invalid data: $data -> "serviceActionName" is missing');
    }
    final sReactionName = data['serviceReactionName'] as String?;
    if (sReactionName == null) {
      throw UnsupportedError(
          'Invalid data: $data -> "serviceReactionName" is missing');
    }
    final aName = data['actionName'] as String?;
    if (aName == null) {
      throw UnsupportedError('Invalid data: $data -> "actionName" is missing');
    }
    final rName = data['reactionName'] as String?;
    if (rName == null) {
      throw UnsupportedError(
          'Invalid data: $data -> "reactionName" is missing');
    }
    final idC = data['id'] as int?;
    if (idC == null) {
      throw UnsupportedError('Invalid data: $data -> "id" is missing');
    }
    final sState = data['state'] as bool?;
    if (sState == null) {
      throw UnsupportedError('Invalid data: $data -> "state" is missing');
    }
    final dDescription = data['description'] as String?;
    if (dDescription == null) {
      throw UnsupportedError(
          'Invalid data: $data -> "reactionName" is missing');
    }
    return ExistingItems(
        serviceActionName: sActionName,
        serviceReactionName: sReactionName,
        actionName: aName,
        reactionName: rName,
        id: idC,
        state: sState,
        description: dDescription);
  }
}
