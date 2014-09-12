// An animatedElementsPanel with aditional facilities to automatically add items
// and one or more button below items. Items and buttons must inherit from
// AnimatedElement. This only takes care of placing elements, you must take care
// of actions connected to buttons in inherited items. You should not change
// position and size of items and buttons
import QtQuick 2.0

AnimatedElementsPanel {
	id: container

	// The items to show
	property var items: []
	// The height of items as a portion of the panel height
	property real itemHeight: 0.1
	// The width of items as a portion of the panel width
	property real itemWidth: 0.7
	// The vertical space between items as a portion of item height
	property real itemSpacing: 0.3

	// The vertical space between the last item and the buttons as a portion
	// of item height
	property real itemButtonsSpacing: 0.3

	// The buttons to show below items
	property var buttons: []
	// The height of buttons as a portion of the panel height
	property real buttonHeight: 0.1
	// The width of buttons as a portion of the panel width
	property real buttonWidth: 0.3
	// The horizontal space between buttons as a portion of button width
	property real buttonSpacing: 0.3

	// The function to place all elements, both items and buttons
	function placeElements()
	{
		// Computing what we can at the beginning (a stands for absolute)
		var aItemHeight = itemHeight * height;
		var aItemWidth = itemWidth * width;
		var aItemSpacing = aItemHeight * itemSpacing;
		var aItemButtonsSpacing = aItemHeight * itemButtonsSpacing;
		var aButtonHeight = buttonHeight * height;
		var aButtonWidth = buttonWidth * width;
		var aButtonSpacing = aButtonWidth * buttonSpacing;

		// The total height occupied by items
		var itemsTotalOccupiedHeight = (items.length == 0) ? 0 : (items.length * aItemHeight + (items.length - 1) * aItemSpacing);
		// The total height occupied by buttons
		var buttonsTotalOccupiedHeight = (buttons.length == 0) ? 0 : aButtonHeight;
		// The total height occupied by all buttons and items
		var totalOccupiedHeight = itemsTotalOccupiedHeight + aItemButtonsSpacing + buttonsTotalOccupiedHeight;
		// The total width occupied by buttons
		var buttonsTotalOccupiedWidth = (buttons.length == 0) ? 0 : (buttons.length * aButtonWidth + (buttons.length - 1) * aButtonSpacing);
		// The y position of the first item
		var firstItemY = (height - totalOccupiedHeight) / 2.0;
		// The x position of the first button
		var firstButtonX = (width - buttonsTotalOccupiedWidth) / 2.0;

		// Computing the position of all items
		var itemsX = (width - aItemWidth) / 2.0;
		for (var i = 0; i < items.length; i++) {
			items[i].x = itemsX;
			if (i == 0) {
				items[i].yWhenVisible = firstItemY;
			} else {
				items[i].yWhenVisible = firstItemY + i * (aItemHeight + aItemSpacing);
			}
			items[i].width = aItemWidth;
			items[i].height = aItemHeight;
		}

		// Now computing the position of all buttons
		var buttonsY = (height + totalOccupiedHeight) / 2.0 - aButtonHeight;
		for (var i = 0; i < buttons.length; i++) {
			buttons[i].yWhenVisible = buttonsY
			if (i == 0) {
				buttons[i].x = firstButtonX;
			} else {
				buttons[i].x = firstButtonX + i * (aButtonWidth + aButtonSpacing);
			}
			buttons[i].width = aButtonWidth;
			buttons[i].height = aButtonHeight;
		}
	}

	// The list of animated elements is the union of the items and buttons
	// lists
	animatedElements: items.concat(buttons)

	// When the list of items or buttons change, the positions are computed
	// again
	onItemsChanged: {
		if (Component.status == Component.Ready) {
			placeElements();
		}
	}
	onButtonsChanged: {
		if (Component.status == Component.Ready) {
			placeElements();
		}
	}

	Component.onCompleted: placeElements()
}
