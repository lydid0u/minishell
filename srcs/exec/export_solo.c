/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_solo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:07:44 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/25 04:08:24 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	export_only(t_copyenv *head)
// {
// 	int alpha;
// 	char lettre;
// 	t_copyenv *current;
// 	t_copyenv *first_sort;
// 	t_copyenv *next;
// 	current = head;
// 	first_sort = NULL;
// 	next = NULL;
// 	lettre = 'A';
// 	alpha = 0;
// 	while (alpha < 26)
// 	{
// 		while (current)
// 		{
// 			if (lettre == current->key[0] && current->written == 0)
// 			{
// 				current->written = 1;
// 				if (first_sort = NULL)
// 				{
// 					first_sort = current;
// 				}
// 				printf("export %s=\"%s\"\n", current->key, current->value);
// 			}
// 			current = current->next;
// 		}
// 		current = head;
// 		lettre++;
// 		alpha++;
// 	}
// }

// void insert_sorted(t_copyenv **head_ref, t_copyenv *new_node) 
// {
//     t_copyenv *current;
//     if (*head_ref == NULL || strcmp((*head_ref)->key, new_node->key) >= 0) 
// 	{
//         new_node->next = *head_ref;
//         *head_ref = new_node;
//     } 
// 	else 
// 	{
//      current = *head_ref;
//      while (current->next != NULL 
		// && strcmp(current->next->key, new_node->key) < 0) 
// 		{
//             current = current->next;
//         }
//         new_node->next = current->next;
//         current->next = new_node;
//     }
// }

// // tri que la 1e lettre donc pas vraiment dans l'ordre
// void export_only(t_copyenv *head) {
//     // Sort the linked list alphabetically by keys
//     t_copyenv *current = head;
//     t_copyenv *sorted = NULL;
//     t_copyenv *next = NULL;
//     while (current != NULL) 
// 	{
// 		next = current->next;
//         insert_sorted(&sorted, current);
//         current = next;
//     }

//     // Export the sorted list
//     current = sorted;
//     while (current != NULL) 
// 	{
//         printf("export %s=\"%s\"\n", current->key, current->value);
//         current = current->next;
//     }
// }
